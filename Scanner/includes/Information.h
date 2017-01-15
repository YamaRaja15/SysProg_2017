#ifndef INFORMATION_H_
#define INFORMATION_H_


class Information {
	public:
		Information(char* lexem);
		virtual ~Information();
		bool matchesLexem(const char* other_lexem);
		const char* getLexem() const;


	private:
		char* lexem;
};

#endif /* INFORMATION_H_ */
