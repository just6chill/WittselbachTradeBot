#include "T++/Framework.h"
#include <iostream>

void Help(Message& Message, Bot& Bot);
void RegSeller(Message& Message, Bot& Bot);
void UnregSeller(Message& Message, Bot& Bot);
void Deposit(Message& Message, Bot& Bot);
void Withdraw(Message& Message, Bot& Bot);
void Balance(Message& Message, Bot& Bot);

int main(int argc, char *argv[]) {

    std::cout << "starting bot" << std::endl;

	Message Message;
	Bot Bot;

	Bot.Token = "Token";

	Bot.Online(Message, [&] {
	    std::cout << "New Message Arrived" << std::endl;
	    std::cout << "-----------------------------" << std::endl;
        std::cout << "user id: " << Message.Data.UserID << std::endl;
        std::cout << "username: " << Message.Data.UserName << std::endl;
        std::cout << "message id: " << Message.Data.MessageID << std::endl;
        std::cout << "date: " << Message.Data.Date << std::endl;
        std::cout << "text: " << Message.Data.Text << std::endl;
        std::cout << "chat id: " << Message.Data.ChatID << std::endl;

        if (Message.Data.Text == "/help") {
            Help(Message, Bot);
        } else if (Message.Data.Text == "/register") {
            RegSeller(Message, Bot);
        } else if (Message.Data.Text == "/unregister") {
            UnregSeller(Message, Bot);
        } else if (Message.Data.Text == "/deposit") {
            Deposit(Message, Bot);
        } else if (Message.Data.Text == "/withdraw") {
            Withdraw(Message, Bot);
        } else if (Message.Data.Text == "/balance") {
            Balance(Message, Bot);
        }
	});

	return 0;
}

void Help(Message& Message, Bot& Bot) {

    std::string Text =
            "available commands:\n"
            "\n"
            "\n"
            "/help\n"
            "shows this\n"
            "\n"
            "/register\n"
            "register is going to create a account for saving and withdrawing resources\n"
            "\n"
            "/unregister\n"
            "unregister is going to delete your resources account. Make sure you sell all your resources before you unregister.\n"
            "\n"
            "/deposit\n"
            "deposit is going to store a specific amount of a specific resource into your account. Use this when you buy.\n"
            "\n"
            "/withdraw\n"
            "withdraw will remove a specific amount of a specific resource from your account. Use this when you sell.\n"
            "\n"
            "/balance\n"
            "balance will show all the resources with a specific amount you are owning.\n"
            "\n"
            "Bot made by @just6chill\n"
            "Note: this bot is still under construction and things may not work\n";

    Message.Reply(0, Bot.Token, Text);
}

void RegSeller(Message& Message, Bot& Bot) {

}

void UnregSeller(Message& Message, Bot& Bot) {

}

void Withdraw(Message& Message, Bot& Bot) {

}

void Deposit(Message& Message, Bot& Bot) {

}

void Balance(Message& Message, Bot& Bot) {

}