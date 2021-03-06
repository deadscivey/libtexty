#include <string>
#include <set>
#include "stopwords/MultiLanguageStopwordFilter.h"
#include "Language.h"
#include "stopwords/english_stopwords.h"
#include "stopwords/french_stopwords.h"
#include "stopwords/german_stopwords.h"
#include "stopwords/italian_stopwords.h"
#include "stopwords/russian_stopwords.h"
#include "stopwords/spanish_stopwords.h"

using namespace std;

namespace texty { namespace stopwords {

bool MultiLanguageStopwordFilter::isStopword(const string &word, Language lang) {
  if (word.size() <= 2) {
    return true;
  }
  switch (lang) {
    case Language::DE : return isGermanStopword(word);
    case Language::EN : return isEnglishStopword(word);
    case Language::ES : return isSpanishStopword(word);
    case Language::FR : return isFrenchStopword(word);
    case Language::IT : return isItalianStopword(word);
    case Language::RU : return isRussianStopword(word);
    default           : return false;
  }
}

}} // texty::stopwords
