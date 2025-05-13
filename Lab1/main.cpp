#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <deque>
#include <cmath>

#define BASE 1000000000
using namespace std;

struct BigNum {
    int length;
    int* digits;
    BigNum(int length);
    BigNum(std::string s);
    BigNum(BigNum* bigNum);
    ~BigNum();
    void reverse();
    void resize();
    BigNum* leftShift(unsigned int numShift);
    BigNum* rightShift(unsigned int numShift);
    std::string toString();
};
struct HandleExpression{
    unordered_set<char> ops = {'+', '-', '*', '/'};
    string redundantOp = "Redundant operator";
    string missingOp = "Missing operator";
    string redundantNum = "Redundant number";
    string missingNum = "Missing number";
    string redundantBracket = "Redundant bracket";
    string missingBracket = "Missing bracket";
    string notNumOrOp = "Not a number or right operator";
    string isValidExpression(std::ifstream& inputFile, bool isOpenBracket = false);
    BigNum* calculateExpression(std::ifstream& inputFile);
    static HandleExpression* getInstance();
    private:
    static HandleExpression* instance;
    HandleExpression(){};
    ~HandleExpression(){
        if(instance != nullptr){
            delete instance;
            instance = nullptr;
        }
    }
};

HandleExpression* HandleExpression::instance = nullptr;

BigNum* evaluateTwoBigNum(BigNum* bigNum1, BigNum* bigNum2, char op);

int isPrecedence(char op1, char op2);
int compareTwoBigNum(BigNum* bigNum1, BigNum* bigNum2);

BigNum* divideTwoBigNum(BigNum* bigNum1, BigNum* bigNum2);
BigNum* schoolBookMutiply(BigNum* bigNum1, BigNum* bigNum2);
BigNum* subtractTwoBigNum(BigNum* bigNum1, BigNum* bigNum2);
BigNum* addTwoBigNum(BigNum* bigNum1, BigNum* bigNum2);

int main(int argc, char* argv[]) {
	string inputFileName = argv[1];
	string outputFileName = argv[2];
	ifstream inputFile(inputFileName);
	ofstream outputFile(outputFileName);
	if (!inputFile.is_open() || !inputFile.is_open()) {
		cout << "Error opening file" << endl;
		return 1;
	}
    HandleExpression* handleExpression = HandleExpression::getInstance();
	while (inputFile.peek() != EOF)
	{
        int begOfExpression = inputFile.tellg();
		if(handleExpression->isValidExpression(inputFile) != ""){
			outputFile<<"Error"<<endl;
			continue;
		}
        inputFile.clear();
		inputFile.seekg(begOfExpression, ios::beg);
		BigNum* result = handleExpression->calculateExpression(inputFile);
		if (!result) {
            outputFile<<"Error";
            char c;
            while(inputFile.get(c) && c != '\n');
        }
		else {
			outputFile<<result->toString();
			delete result;
            result = nullptr;
		}
		outputFile<<endl;
	}

	inputFile.close();
	outputFile.close();
	return 0;
}

HandleExpression* HandleExpression::getInstance() {
    if (instance == nullptr) {
        instance = new HandleExpression();
    }
    return instance;
}

BigNum* evaluateTwoBigNum(BigNum* bigNum1, BigNum* bigNum2, char op) {

    BigNum* result = nullptr;
    BigNum* operand1 = new BigNum(bigNum1);
    BigNum* operand2 = new BigNum(bigNum2);
    int* sign1 = &operand1->digits[operand1->length - 1];
    int* sign2 = &operand2->digits[operand2->length - 1];
    long long multSign = static_cast<long long>(*sign1) * (*sign2);
    switch (op) {
    case '+': {
        //-a+b = -(a-b)
        //a+(-b) = a-b
        if (multSign < 0) {
            *sign1 = abs(*sign1);
            *sign2 = abs(*sign2);
            result = evaluateTwoBigNum(operand1, operand2,'-');
            if(bigNum1->digits[bigNum1->length - 1] < 0){
                result->digits[result->length - 1] *= -1;
            }
        }
        //-a+(-b) = -(a+b)
        // a+b    =   a+b 
        else if (multSign > 0) {
            *sign1 = abs(*sign1);
            *sign2 = abs(*sign2);
            result = addTwoBigNum(operand1, operand2);
            if(bigNum1->digits[operand1->length - 1] < 0)
                result->digits[result->length - 1] *= -1;
        } 
        // a+0 = a
        // 0+b = b
        else if (multSign == 0) {
            if (*sign1 == 0) {
                result = new BigNum(operand2);
            } else {
                result = new BigNum(operand1);
            }
        }
        break;
    }
    case '-': {
        if (multSign > 0) {
            if (*sign1 > 0) {
                if (compareTwoBigNum(operand1, operand2) > 0) {
                    result = subtractTwoBigNum(operand1, operand2);
                } else {
                    result = subtractTwoBigNum(operand2, operand1);
                    result->digits[result->length - 1] *= -1;
                }
            } 
            // -a-(-b) = -(a-b)
            else {
                *sign1 = abs(*sign1);
                *sign2 = abs(*sign2);
                result = evaluateTwoBigNum(operand1, operand2, '-');
                result->digits[result->length - 1] *= -1;
            }
        } 
        // -a-b = -(a+b)
        // a-(-b) = a+b
        else if (multSign < 0) {
            *sign1 = abs(*sign1);
            *sign2 = abs(*sign2);
            result = addTwoBigNum(operand1, operand2);
            if(bigNum1->digits[bigNum1->length -1] < 0){
                result->digits[result->length - 1] *= -1;
            }
        }
        else if(multSign == 0){
            if (*sign1 == 0) {
                result = new BigNum(operand2);
            } else {
                result = new BigNum(operand1);
            }
        }
        break;
    }
    case '*': {
        *sign1 = abs(*sign1);
        *sign2 = abs(*sign2);
        result = schoolBookMutiply(operand1, operand2);
        result->digits[result->length - 1] *= multSign < 0 ? -1 : 1;
        break;
    }
    case '/': {
        if (*sign2 == 0) break;
        if (multSign < 0) {
            *sign1 = abs(*sign1);
            *sign2 = abs(*sign2);
        }
        result = divideTwoBigNum(operand1, operand2);
        result->digits[result->length - 1] *= multSign < 0 ? -1 : 1;
        break;
    }
    }

    delete operand1;
    delete operand2;
    if(result) result->resize();
    return result;
}

BigNum::BigNum(int length) {
    this->length = length;
    this->digits = new int[this->length]();
}

BigNum::BigNum(string s) {
    bool isNegative = false;
    if (s[0] == '-') {
        s.erase(0, 1);
        isNegative = true;
    }
    if (s[0] == '+') s.erase(0, 1);
    this->length = ceil((double)s.length()/log10(BASE));
    this->digits = new int[this->length]();

    int maxLengthOfDigit = (int)log10(BASE);
    for (int i = 0, j = s.length(); j > 0; i++, j -= maxLengthOfDigit) {
        int start = max(0, j - maxLengthOfDigit);
        this->digits[i] = stoi(s.substr(start, j - start));
    }

    if (isNegative) {
        this->digits[this->length - 1] = -this->digits[this->length - 1];
    }
}

BigNum::BigNum(BigNum* bigNum){
	this->length = bigNum->length;
	this->digits = new int[this->length];
	for(int i = 0; i < this->length; i++){
		this->digits[i] = bigNum->digits[i];
	}
}

BigNum::~BigNum(){
	delete[] digits;
}

string BigNum::toString(){
	string s;
	int* sign = &this->digits[this->length -1];
	bool isNegative = *sign < 0;
	if(isNegative){
		s.push_back('-');
		*sign *= -1;
	}
	s += to_string(*sign);
	for(int i = this->length - 2; i >= 0; i--){
        int temp = this->digits[i];
		int nDigit = log10(this->digits[i]) + 1;
		while(nDigit < (int)log10(BASE)){
			s.push_back('0');
			nDigit++;
		}
		s += to_string(this->digits[i]);
	}
	
	if(isNegative){
		*sign *= -1;
	}
	return s;
    this->resize();
}

void BigNum::resize(){
	int countZero = 0;
	for(int i = this->length -1; i > 0; i--){
		if(this->digits[i] != 0) break;
		countZero++;
	}
	if(countZero == 0) return;
	this->length -= countZero;
	int* newDigits = new int[this->length]();
	for(int i =0; i < this->length; i++){
		newDigits[i] = this->digits[i];
	}
	int* temp = this->digits;
	this->digits = newDigits;
	delete[] temp;
}

BigNum* HandleExpression::calculateExpression(ifstream& inputFile){
	deque<BigNum*> threeNumberHandler;
	deque<char> opsHandler;
    HandleExpression* handleExpression = HandleExpression::getInstance();
	char c;
    inputFile.get(c);
    while(c == ' ' && inputFile.get(c));

    if(c != '+' && c != '-'){
        inputFile.unget();
    }
	string s;
	if(c == '-' || c == '+'){
		s.push_back(c);
		while(inputFile.get(c) && c >= '0' && c <= '9'){
			s.push_back(c);
		}
		inputFile.unget();
		threeNumberHandler.push_back(new BigNum(s));
	}

    while (inputFile.get(c) && c != '\n' && c != ')') {
        if(c == ' ') continue;
		if(threeNumberHandler.size() == 3){
			if(isPrecedence(opsHandler[0],opsHandler[1]) >= 0){
				BigNum* bigNum1 = threeNumberHandler.front();
				threeNumberHandler.pop_front();
				BigNum* bigNum2 = threeNumberHandler.front();
				threeNumberHandler.pop_front();
				char op = opsHandler.front();
				opsHandler.pop_front();
				BigNum* res = evaluateTwoBigNum(bigNum1,bigNum2,op);
				delete bigNum1;
				delete bigNum2;
				if(res == nullptr) return res;
				threeNumberHandler.push_front(res);
			}
			else{
				BigNum* bigNum1 = threeNumberHandler.back();
				threeNumberHandler.pop_back();
				BigNum* bigNum2 = threeNumberHandler.back();
				threeNumberHandler.pop_back();
				char op = opsHandler.back();
				opsHandler.pop_back();
				BigNum* res = evaluateTwoBigNum(bigNum1,bigNum2,op);
				delete bigNum1;
				delete bigNum2;
				if(res == nullptr) return res;
				threeNumberHandler.push_back(res);
			}
		}
        if (c >= '0' && c <= '9') {
            string s;
			s.push_back(c);
            while (inputFile.get(c) && c >= '0' && c <= '9' && c != '\n'){
				s.push_back(c);
			}
            inputFile.unget();
			threeNumberHandler.push_back(new BigNum(s));
            continue;
        }

        if (ops.count(c)) {
            opsHandler.push_back(c);
            continue;
        }

        if (c == '(') {
			BigNum* res = calculateExpression(inputFile);
			threeNumberHandler.push_back(res);
            continue;
        }
    }
	while(threeNumberHandler.size() > 1){
		if(isPrecedence(opsHandler.front(),opsHandler.back()) >= 0){
			BigNum* bigNum1 = threeNumberHandler.front();
			threeNumberHandler.pop_front();
			BigNum* bigNum2 = threeNumberHandler.front();
			threeNumberHandler.pop_front();
			char op = opsHandler.front();
			opsHandler.pop_front();
			BigNum* res = evaluateTwoBigNum(bigNum1,bigNum2,op);
			delete bigNum1;
			delete bigNum2;
			if(res == nullptr) return res;
			threeNumberHandler.push_front(res);
		}
		else{
			BigNum* bigNum2 = threeNumberHandler.back();
			threeNumberHandler.pop_back();
			BigNum* bigNum1 = threeNumberHandler.back();
			threeNumberHandler.pop_back();
			char op = opsHandler.back();
			opsHandler.pop_back();
			BigNum* res = evaluateTwoBigNum(bigNum1,bigNum2,op);
			delete bigNum1;
			delete bigNum2;
			if(res == nullptr) return res;
			threeNumberHandler.push_back(res);
		}
	}
	return threeNumberHandler.back();
}

string HandleExpression::isValidExpression(ifstream& inputFile, bool isOpenBracket){
	bool numberBefore = false, opBefore = false;
    HandleExpression* handleExpression = HandleExpression::getInstance();

    char c;
    if(!inputFile.get(c) && c == '\n' && c == ')'){
        return isOpenBracket ? missingBracket : "";
    }

    while(c == ' ' && inputFile.get(c));

    if(c != '+' && c != '-'){
        inputFile.unget();
    }

    while (inputFile.get(c) && c != '\n' && c != ')') {
        if(c == ' ') continue;

        if (c >= '0' && c <= '9') {
            if (numberBefore) return redundantNum + " or " + missingOp;
            numberBefore = true;
            opBefore = false;
            while (inputFile.get(c) && c >= '0' && c <= '9' && c != '\n');
            inputFile.unget();
            continue;
        }

        if (ops.count(c)) {
            if (opBefore || !numberBefore) return redundantOp + " or " + missingNum;
            opBefore = true;
            numberBefore = false;
            continue;
        }

        if (c == '(') {
            if(numberBefore) return redundantNum + " or " + missingOp;
            std::string res = isValidExpression(inputFile, true);
            if (res != "") return res;
            numberBefore = true;
            opBefore = false;
            continue;
        }

        return notNumOrOp;
    }

    if (!numberBefore || opBefore) return missingNum + " or " + redundantOp;
    
    if( c == ')' && !isOpenBracket) return redundantBracket;
    if( c != ')' && isOpenBracket) return missingBracket;
    return "";
}

int isPrecedence(char op1, char op2)
{
	unordered_map<char, char> precedence1 = {{'+',1},{'-',1}};
	unordered_map<char, char> precedence2 = {{'*',2},{'/',2}};

	unordered_map<char, char> precedence;
	precedence.insert(precedence1.begin(),precedence1.end());
	precedence.insert(precedence2.begin(),precedence2.end());

	if(precedence[op1] < precedence[op2]) return -1;
	else if(precedence[op1] > precedence[op2]) return 1;
	return 0;
}

int compareTwoBigNum(BigNum* bigNum1, BigNum* bigNum2) {
	int* sign1 = &bigNum1->digits[bigNum1->length - 1];
    int* sign2 = &bigNum2->digits[bigNum2->length - 1];
    bool isNegative = false;
	long long multSign =static_cast<long long>( *sign1) * (*sign2);
	if(multSign < 0){
		return bigNum1->digits[bigNum1->length-1] > 0 ? 1:-1;
	}

	if(*sign1 < 0){
		swap(bigNum1,bigNum2);
        isNegative = true;
        *sign1 *= -1;
        *sign2 *= -1;
	}

	if(bigNum1->length != bigNum2->length){
		return bigNum1->length > bigNum2->length;
	}

	for (int i = bigNum1->length -1; i >= 0; i--)
	{
		if (bigNum1->digits[i] > bigNum2->digits[i]) return 1;
		if (bigNum1->digits[i] < bigNum2->digits[i]) return -1;
	}
    if(isNegative){
        *sign1 *= -1;
        *sign2 *= -1;
    }
	return 0;
}

BigNum* addTwoBigNum(BigNum* bigNum1, BigNum* bigNum2) {
	BigNum* result = new BigNum(max(bigNum1->length,bigNum2->length) + 1);

	int carry = 0;
	int length = max(bigNum1->length, bigNum2->length);
	for (int i = 0; i < length || carry != 0; i++) {
		long long sum = carry;
		sum += i >= bigNum1->length ? 0 : bigNum1->digits[i];
		sum += i >= bigNum2->length ? 0 : bigNum2->digits[i];
		result->digits[i] = sum % BASE;
		carry = sum / BASE;
	}
	result->resize();
	return result;
}

BigNum* subtractTwoBigNum(BigNum* bigNum1, BigNum* bigNum2) {
	BigNum* result = new BigNum(max(bigNum1->length,bigNum2->length));
	
	int carry = 0;
	int length = max(bigNum1->length,bigNum2->length);

	for (int i = 0; i < length || carry != 0; i++)
	{
		long long diff = 0;
		diff += i >= bigNum1->length ? 0 : bigNum1->digits[i];
		diff -= i >= bigNum2->length ? 0 : bigNum2->digits[i];
		diff -= carry;

		result->digits[i] = diff < 0 ? diff + BASE : diff;
		carry = diff < 0 ? 1 : 0;
	}
	result->resize();
	return result;
}

BigNum* BigNum::leftShift(unsigned int numShift){
	BigNum* newBigNum = new BigNum(this->length + numShift);
	for(int i = 0; i < this->length; i++){
		newBigNum->digits[i + numShift] = this->digits[i];
	}

    newBigNum->resize();
	return newBigNum;
}

BigNum* BigNum::rightShift(unsigned int numShift){
	BigNum* newBigNum = new BigNum(this->length - numShift);
	for(int i = numShift; i < this->length; i++){
		newBigNum->digits[i-numShift] = this->digits[i];
	}

    newBigNum->resize();
	return newBigNum;
}

BigNum* schoolBookMutiply(BigNum* bigNum1, BigNum* bigNum2){
	BigNum* result = new BigNum(bigNum1->length + bigNum2->length);
	for(int i = 0; i < bigNum1->length; i++){
		int carry = 0;
		for(int j = 0; j < bigNum2->length; j++){
			long long mult = static_cast<long long>(bigNum1->digits[i]) * bigNum2->digits[j] + carry + result->digits[i+j];
			carry = mult/BASE;
			result->digits[i+j] = mult%BASE;
		}
		result->digits[i + bigNum2->length] = carry;
	}
	result->resize();
	return result;
}

void BigNum::reverse() {
	int haft = this->length/2;
	for(int i = 0; i < haft; i++){
		swap(this->digits[i],this->digits[this->length -1- i]);
	}
}

BigNum* divideTwoBigNum(BigNum* bigNum1, BigNum* bigNum2) {
    if(compareTwoBigNum(bigNum1, bigNum2) < 0){
        return new BigNum(1);
    }
    if(bigNum2->length == 1 && bigNum2->digits[bigNum2->length-1] == 0) return nullptr;
    int norm = BASE/(bigNum2->digits[bigNum2->length -1] + 1);
    BigNum* temp = new BigNum(1);
    temp->digits[0] = norm;
    bigNum1 = schoolBookMutiply(bigNum1,temp);
    bigNum2 = schoolBookMutiply(bigNum2,temp);
    delete temp;
    BigNum* quotient = new BigNum(bigNum1->length);
    BigNum* remainder = new BigNum(1);

    for(int i = bigNum1->length - 1; i >= 0; i--){
        temp = remainder->leftShift(1);
        BigNum* bigNum1_i = new BigNum(1);
        bigNum1_i->digits[0] = bigNum1->digits[i];
        delete remainder;
        remainder = addTwoBigNum(temp, bigNum1_i);
        delete temp, bigNum1_i;
        //abcdef/defigh: a/d || ab/d
        int coef1 = remainder->length <= bigNum2->length ? 0 : remainder->digits[bigNum2->length];
        int coef2 = remainder->length <  bigNum2->length ? 0 : remainder->digits[bigNum2->length -1];

        long long q = ((long long)coef1*BASE + coef2)/bigNum2->digits[bigNum2->length -1];
        //Create a BigNum q;
        long long d = q;
        int length = q == 0 ? 1 : log(d)/log(BASE) + 1;
        temp = new BigNum(length);
        for(int i = 0; i < length; i++){
            temp->digits[i] = d%BASE;
            d /= BASE;
        }
        temp->resize();

        //ab/d = e, ab - e*d
        BigNum* temp1 = schoolBookMutiply(temp,bigNum2);
        BigNum* temp2 = evaluateTwoBigNum(remainder,temp1,'-');
        delete temp, temp1;
        //if rem = ab - e*d < 0 then fix till rem >= 0
        while(temp2->digits[temp2->length -1] < 0){
            temp = evaluateTwoBigNum(temp2,bigNum2,'+');
            delete temp2;
            temp2 = temp;
            q--;
        }
        delete remainder;
        remainder = temp2;
        quotient->digits[i] = q;
    }
    quotient->resize();
    delete remainder;
    return quotient;
}