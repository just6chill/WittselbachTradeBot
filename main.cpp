#include "T++/Framework.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <ostream>
#include <fstream>

void Help(Message& Message, Bot& Bot);
int RegSeller(Message& Message, Bot& Bot);
void UnregSeller(Message& Message, Bot& Bot);
void Deposit(Message& Message, Bot& Bot);
void Withdraw(Message& Message, Bot& Bot);
int Balance(Message& Message, Bot& Bot);

void tokenize(std::string const &str, const char delim,
              std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

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

        std::string input = Message.Data.Text;
        std::string word = input.substr(0, input.find(" "));

        if (word == "/help") {
            Help(Message, Bot);
        } else if (word == "/register") {
            RegSeller(Message, Bot);
        } else if (word == "/unregister") {
            UnregSeller(Message, Bot);
        } else if (word == "/deposit") {
            Deposit(Message, Bot);
        } else if (word == "/withdraw") {
            Withdraw(Message, Bot);
        } else if (word == "/balance") {
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

    Message.TextReply(0, Bot.Token, Text);

}

int RegSeller(Message& Message, Bot& Bot) {
    const char delim = ' ';

    std::vector<std::string> out;
    tokenize(Message.Data.Text, delim, out);

    if (out.size() != 3) {
        Message.TextReply(0, Bot.Token, "usage: \n\n/register @username rrid");
        return 1;
    } else if ((Message.Data.UserName != "just6chill") && (Message.Data.UserName != "Geistheiler") && (Message.Data.UserName != "TVFOM")) {
        Message.TextReply(0, Bot.Token, "you're not authorised to use this command");
        return 1;
    }

    std::ifstream DB("TradeDB.txt");
    std::string Line;
    while (std::getline(DB, Line))
    {
        std::string word = Line.substr(0, Line.find(" "));
        if (out[1] == word) {
            Message.TextReply(0, Bot.Token, "Mentioned user is already registered");
            return 1;
        }
    }

    std::ostringstream text;
    text << "Registering Trader:\n\n" << "Telegram: " << out[1].c_str() << "\n" << "RR: " << out[2].c_str();
    Message.SendText(0, Bot.Token, text.str());

    std::ofstream Database;
    Database.open("TradeDB.txt", std::ofstream::app);
    Database << out[1].c_str() << " " << out[2].c_str() << " 0 0 0 0 0 0 \n";
    Database.close();

    return 0;
}

void UnregSeller(Message& Message, Bot& Bot) {

}

void Withdraw(Message& Message, Bot& Bot) {

}

void Deposit(Message& Message, Bot& Bot) {

}

int Balance(Message& Message, Bot& Bot) {

    const char delim = ' ';
    std::vector<std::string> out;
    tokenize(Message.Data.Text, delim, out);

    if (out.size() != 2) {
        Message.TextReply(0, Bot.Token, "usage: \n\n/balance @username");
        return 1;
    }

    std::ifstream DB("TradeDB.txt");
    std::string Line;

    std::string UserName, UserID;
    int Money, Gold, Oil, Ore, Uranium, Diamonds;
    while (std::getline(DB, Line)) {
        if (Line.substr(0, Line.find(" ")) == out[1]) {
            std::istringstream iss(Line);
            if (!(iss >> UserName >> UserID >> Money >> Gold >> Oil >> Ore >> Uranium >> Diamonds)) { break; }
        }
    }

    if (UserName.empty()) {
        Message.SendText(0, Bot.Token, "mentioned user isn't existing");
        return 1;
    }
    std::ostringstream text;
    text << "Budget of Trader " << UserName << " :\n" << "Money: " << Money << "\n" << "Gold: " << Gold << "\n" << "Oil: " << Oil << "\n" << "Ore: " << Ore << "\n" << "Uranium: " << Uranium << "\n" << "Diamonds: " << Diamonds << "\n";
    Message.SendText(0, Bot.Token, text.str());

    return 0;
    }
