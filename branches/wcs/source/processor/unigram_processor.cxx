#include <cwchar>
#include <cassert>
#include <iostream>

#include "lexicon_factory.hxx"
#include "unigram_processor.hxx"

UnigramProcessor::UnigramProcessor(IConfig *config)
{
	const char *s;

	config->get_value("ele_lambda", _lambda);
	config->get_value("lexicon_unigram", s);
	config->get_value("max_token_length", _max_token_length);
	_lexicon = LexiconFactory::load(s);

	_token = new wchar_t[_max_token_length + 1]; /* x4 for unicode */
}

UnigramProcessor::~UnigramProcessor()
{
	delete []_token;
	delete _lexicon;
}

void UnigramProcessor::_process(LexToken *token, std::vector<LexToken *> &out)
{
	size_t i, j, length, max_token_length, *backref;
	double *score, lp;
	size_t num_terms, num_types;
	wchar_t *s;

	num_terms = _lexicon->sum_value();
	num_types = _lexicon->num_insert();

	s = token->get_token();
	length = token->get_length();
	score = new double[length + 1];
	backref = new size_t[length + 1];

	for (i = 0; i <= length; i++) {
		score[i] = -1e300;
		backref[i] = 0;
	}

	/* Calculate score using DP */
	score[0] = 0;
	for (i = 0; i < length; i++) {
		max_token_length = (_max_token_length < length - i)?_max_token_length:length - i;
		bool found = false;
		for (j = 1; j <= max_token_length; j++) {
			wcsncpy(_token, s + i, j);
			_token[j] = L'\0';
			int v = _lexicon->search(_token);
			if (v > 0) {
				lp = _ele_estimate(v, num_terms, num_types);
				if (score[i + j] < score[i] + lp) {
					score[i + j] = score[i] + lp;
					backref[i + j] = i;
					found = true;
				}
			}
		}

		if (!found) {
			lp = _ele_estimate(0, num_terms, num_types);
			j = 1;
			if (score[i + j] < score[i] + lp) {
				score[i + j] = score[i] + lp;
				backref[i + j] = i;
			}
		}
	}

	assert(stack.empty() == true);
	for (i = length; i > 0;) {
		wcsncpy(_token, s + backref[i], i - backref[i]);
		_token[i - backref[i]] = L'\0';
		stack.push(new LexToken(_token, LexToken::attr_cword));
		i = backref[i];
	}
	while(!stack.empty()) {
		out.push_back(stack.top());
		stack.pop();
	}
	delete []score;
	delete []backref;
}