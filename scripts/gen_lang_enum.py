import os
LANGUAGE_PROFILES_PATH = 'external/langdetect/langdetect/profiles'


if __name__ == '__main__':
    names = map(
        lambda x: x.replace('-', '_').upper(),
        os.listdir(LANGUAGE_PROFILES_PATH)
    )
    names.append('UNKNOWN')
    names.sort()
    print 'enum class Language {'
    for i in xrange(len(names)):
        name = names[i]
        line = '  %s' % name
        if i < (len(names) - 1):
            line += ','
        print line
    print '};\n'

    print '\n\n'

    print 'std::string stringOfLanguage(Language lang) {'
    print '  switch(lang) {'
    for name in names:
        print '    case Language::%s : return "%s";' % (name, name.lower())
    print '    default : return "NOT_RECOGNIZED";'
    print '  }'
    print '}'
    print '\n'
    print 'static const unordered_map<string, Language> codeToLanguageMap {'
    for i, name in enumerate(names):
        line = '  {"%s", %s}' % (name.lower(), 'Language::%s' % name)
        if i < len(names) - 1:
            line += ','
        print line
    print '};'
