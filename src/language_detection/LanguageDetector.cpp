#include "language_detection/LanguageDetector.h"
#include "language_detection/DetectionRunner.h"
#include "string_views/RandomAccessNGramView.h"
#include "string_views/NGramSampler.h"
#include "randomness/RandomDistribution.h"
#include "Language.h"

using namespace std;

namespace texty { namespace language_detection {

using string_views::NGramSampler;
using string_views::RandomAccessNGramView;
using randomness::RandomDistribution;
using sampler_type = NGramSampler<
  RandomDistribution<std::uniform_int_distribution, size_t>
>;

LanguageDetector::LanguageDetector(LanguageProfiles profiles)
  : profiles_(std::move(profiles)){}

Language LanguageDetector::detect(const string &text, size_t seed) {
  auto ngramView = RandomAccessNGramView::create(text);
  DetectionRunner::sampler_type sampler(std::move(ngramView), seed);
  DetectionRunner runner(profiles_, sampler);
  return runner.detect();
}

std::map<Language, double> LanguageDetector::getProbabilities(const string &text, size_t seed) {
  auto ngramView = RandomAccessNGramView::create(text);
  DetectionRunner::sampler_type sampler(std::move(ngramView), seed);
  DetectionRunner runner(profiles_, sampler);
  return runner.getProbabilities();
}

}} // texty::language_detection