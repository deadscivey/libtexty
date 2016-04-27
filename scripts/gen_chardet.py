import os

HERE = os.path.dirname(os.path.realpath(__file__))
OUTPUT_DIR = os.path.join(
    HERE,
    '../src/chardet/generated'
)
from util.cpp_formatters import CPPDeclaration, CPPInitializerList

def handle_jisfreq():
    from chardet.jisfreq import JISCharToFreqOrder, JIS_TABLE_SIZE, JIS_TYPICAL_DISTRIBUTION_RATIO
    jis_table = CPPDeclaration('static const std::vector<int>', 'JIS_CHAR_TO_FREQ_ORDER',
        CPPInitializerList(JISCharToFreqOrder)
    )
    return '\n'.join([
        '#include <vector>',
        'using namespace std;',
        str(jis_table) + ';'
    ])

if __name__ == '__main__':
    out = handle_jisfreq()
    with open(os.path.join(OUTPUT_DIR, 'jisfreq.cpp'), 'w') as f:
        f.write(out)

