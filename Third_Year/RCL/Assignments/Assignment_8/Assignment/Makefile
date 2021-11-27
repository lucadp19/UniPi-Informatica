GSON_PATH=../../libs/gson-2.8.6.jar
ACCOUNTS_FILE=accounts.json

Assignment.class : Assignment.java BankAccount.java BankAccountCreator.java Causal.java
	javac -cp $(GSON_PATH):. Assignment.java BankAccountCreator.java

.PHONY: clean-tmp run clean 

clean-tmp:
	rm $(ACCOUNTS_FILE)

clean:
	rm *.class
	rm $(ACCOUNTS_FILE)

run:
	java -cp $(GSON_PATH):. Assignment

