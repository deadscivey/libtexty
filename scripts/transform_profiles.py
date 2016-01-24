import sys
import json
import os
from collections import defaultdict
from cStringIO import StringIO

LANGUAGE_PROFILES_PATH = 'external/langdetect/langdetect/profiles'

def list_in_dir(dirpath):
    return map(lambda x: os.path.join(dirpath, x), os.listdir(dirpath))

def load_profiles(use_enum_names=True):
    profs = list_in_dir(LANGUAGE_PROFILES_PATH)
    profiles = []
    for lang_file in profs:
        with open(lang_file) as f:
            prof_data = json.load(f)
            word_counts = map(float, prof_data['n_words'])
            gram_freqs = prof_data['freq']
            xformed_freqs = [{}, {}, {}]
            for k, v in prof_data['freq'].iteritems():
                k = tuple(map(ord, k))
                ngram_type = len(k)
                xformed_freqs[ngram_type-1][k] = float(v) / word_counts[ngram_type-1]
            lang_name = prof_data['name'].replace('-', '_')
            if use_enum_names:
                lang_name = 'Language::%s' % lang_name.upper()
            profiles.append({
                'name': lang_name,
                'scores': xformed_freqs
            })
    return profiles

def invert_profiles(profiles):
    grams = [defaultdict(lambda: defaultdict(dict)) for _ in xrange(3)]
    for prof in profiles:
        name = prof['name']
        for n, prof_grams in enumerate(prof['scores']):
            for key, score in prof_grams.iteritems():
                g = grams[n]
                g_scores = g[key]
                g_scores[name] = score
    return grams

def get_ngram_sig(n):
    return "NGram<uint32_t, %s>" % n

def get_inner_map_sig(n=None):
    return 'std::unordered_map<Language, double>'

def get_outer_map_sig(n):
    gram_map_sig = 'std::unordered_map<%s, %s>' % (
        get_ngram_sig(n), get_inner_map_sig()
    )
    return gram_map_sig

def emit_json(fptr):
    grams = invert_profiles(load_profiles(use_enum_names=False))
    out = []
    for g in grams:
        items = []
        for ngram, scores in g.iteritems():
            scores = scores.items()
            scores.sort(key=lambda x: x[0])
            items.append([ngram, scores])
        out.append(items)
    fptr.write(json.dumps(out))

def emit_score_map(fptr, start_indent=0):
    grams = invert_profiles(load_profiles())
    gram_names = ['one', 'two', 'three']
    for n, (name, scores) in enumerate(zip(gram_names, grams)):
        n = n + 1
        lines = []
        inner_map_sig = get_inner_map_sig()
        ngram_sig = get_ngram_sig(n)
        gram_map_sig = get_outer_map_sig(n)

        lines.append("const %s %s_grams {" % (gram_map_sig, name))
        gram_map_items = []
        for ord_tuple, lang_scores in scores.iteritems():
            ngram_item = "%s { %s }" % (ngram_sig, ', '.join(map(str, ord_tuple)))
            lang_subitems = ['{ %s, %s }' % (l, s) for l, s in lang_scores.iteritems()]
            lang_item = '%s { %s }' % (inner_map_sig, ', '.join(lang_subitems))
            gram_map_items.append("{ %s, %s }" % (ngram_item, lang_item))

        item_count = len(gram_map_items)
        for i, item in enumerate(gram_map_items):
            line = "  %s" % item
            if i < (item_count - 1):
                line += ","
            lines.append(line)
        lines.append("};")
        if start_indent > 0:
            spaces = ' ' * start_indent
            lines = map(lambda x: "%s%s" % (spaces, x), lines)
        fptr.write("\n".join(lines))


def emit_impl(fptr):
    prelude = [
        "#include <unordered_map>",
        "#include <map>",
        '#include "Language.h"',
        '#include "NGram.h"',
        '#include "language_detection/profile_data.h"',
        '',
        'namespace texty { namespace language_detection {',
        ''
    ]

    fptr.write('\n'.join(prelude))
    emit_score_map(fptr)
    n_names = ['one', 'two', 'three']
    func_names = ['get_%s_grams' % n for n in n_names]
    func_sigs = []
    for n in xrange(len(n_names)):
        func_sigs.append('const %s &' % get_outer_map_sig(n+1))
    accessors = []
    for i in xrange(len(n_names)):
        lines = [
            '%s %s() {' % (func_sigs[i], func_names[i]),
            '  return %s_grams;' % n_names[i],
            '}'
        ]
        fptr.write('\n')
        fptr.write('\n'.join(lines))
    end = [
        '',
        '}} // texty::language_detection'
    ]
    fptr.write('\n'.join(end))

def emit_header(fptr):
    lines = ["#pragma once"]
    for inc in ['<unordered_map>', '<map>', '"NGram.h"', '"Language.h"']:
        lines.append("#include %s" % inc)
    lines.extend([
        "",
        "namespace texty { namespace language_detection {",
        ""
    ])
    names = "one", "two", "three"
    for i, name in enumerate(names):
        return_sig = 'const %s &' % get_outer_map_sig(i+1)
        declaration = '%s get_%s_grams();' % (return_sig, name)
        lines.append(declaration)
    lines.extend([
        "",
        "}} // texty::language_detection",
        ""
    ])
    fptr.write('\n'.join(lines))

def throw_usage():
    print 'usage: [script] header|impl|json'
    raise ValueError

if __name__ == '__main__':
    fptr = StringIO()
    if len(sys.argv) < 2:
        throw_usage()
    if sys.argv[1] == 'header':
        emit_header(fptr)
    elif sys.argv[1] == 'impl':
        emit_impl(fptr)
    elif sys.argv[1] == 'json':
        emit_json(fptr)
    else:
        throw_usage()
    fptr.seek(0)
    print fptr.read()
