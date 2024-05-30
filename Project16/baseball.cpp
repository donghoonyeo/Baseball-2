#include <stdexcept>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question) : 
		question(question) {}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		GuessResult result = { false, 0, 0 };

		result.strikes = checkStrikesCnt(guessNumber);
		if (result.strikes == question.size()) {
			result.solved = true;
			return result;
		}

		result.balls = checkBallsCnt(guessNumber);
		
		return result;
	}

	void assertIllegalArgument(const string& guessNumber)
	{
		if (guessNumber.length() != 3)
			throw length_error("Must be three letters.");

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber))
			throw invalid_argument("Must not have the same number");
	}

	bool isDuplicatedNumber(const string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

	int checkStrikesCnt(const string& guessNumber) {
		int strikesCnt = 0;
		for (int i = 0; i < question.size(); i++) {
			if (guessNumber[i] == question[i])
				strikesCnt++;
		}
		return strikesCnt;
	}

	int checkBallsCnt(const string& guessNumber) {
		int ballCnt = 0;
		for (int i = 0; i < question.size(); i++) {
			for (int j = 0; j < question.size(); j++) {
				if (i == j) continue;
				if (guessNumber[i] == question[j]) {
					ballCnt++;
					break;
				}
			}
		}
		return ballCnt;
	}

private:
	string question;
};