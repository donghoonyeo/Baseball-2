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
		return checkResult(guessNumber);
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

private:
	string question;

	bool isDuplicatedNumber(const string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

	int checkStrikesCnt(const string& guessNumber) {
		int strikesCnt = 0;
		for (int index = 0; index < question.size(); index++) {
			if (guessNumber[index] == question[index]) {
				strikesCnt++;
			}
		}
		return strikesCnt;
	}

	int checkBallsCnt(const string& guessNumber) {
		int ballCnt = 0;
		for (int guessIndex = 0; guessIndex < guessNumber.size(); guessIndex++) {
			for (int questIndex = 0; questIndex < question.size(); questIndex++) {
				if (guessIndex == questIndex) continue;
				if (guessNumber[guessIndex] == question[questIndex]) {
					ballCnt++;
					break;
				}
			}
		}
		return ballCnt;
	}

	GuessResult checkResult(const string& guessNumber) {
		GuessResult result = { false, 0, 0 };
		result.strikes = checkStrikesCnt(guessNumber);
		if (result.strikes == question.size()) {
			result.solved = true;
			return result;
		}
		result.balls = checkBallsCnt(guessNumber);
		return result;
	}
};