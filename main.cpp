#include "T++/Framework.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <ostream>
#include <fstream>
#include <limits>

void Help(Message& Message, Bot& Bot);
int RegSeller(Message& Message, Bot& Bot);
void UnregSeller(Message& Message, Bot& Bot);
int Deposit(Message& Message, Bot& Bot);
int Withdraw(Message& Message, Bot& Bot);
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

    Bot.Token = "token";

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

int Withdraw(Message& Message, Bot& Bot) {

    // /withdraw user type amount
    const char delim = ' ';
    std::vector<std::string> out;
    tokenize(Message.Data.Text, delim, out);

    if (out.size() != 3) {
        Message.TextReply(0, Bot.Token, "usage: \n\n/withdraw Type amount\nresource: (M - Money, G - Gold, O - Oil, R - Ore, U - Uranium, D - Diamonds)");
        return 1;
    }

    std::ifstream DBRead("TradeDB.txt");
    std::string Line;
    std::ofstream DBWrite;

    DBWrite.open("Temp.txt", std::ofstream::app);;

    std::string UserName, UserID;
    long long int Money, Gold, Oil, Ore, Uranium, Diamonds;

    std::string User = "@";
    User.append(Message.Data.UserName);

    bool UserFlag = false;
    bool PoorFlag = false;
    while (std::getline(DBRead, Line)) {
        if (Line.substr(0, Line.find(" ")) == User) {
            long long int Amount;
            try {
                //shits not workin
                Amount = std::stoll(out[2]);
            }
            catch (...) {
                Amount = 0;
            }
            std::istringstream iss(Line);
            if (!(iss >> UserName >> UserID >> Money >> Gold >> Oil >> Ore >> Uranium >> Diamonds)) { break; }

            if (UserName == User) {

                UserFlag = true;
                switch (out[1][0]) {
                    case 'M':
                        if (Amount <= Money) {
                            Money -= Amount;
                        } else {
                            Message.SendText(0, Bot.Token, "you dont have enough money :(");
                            PoorFlag = true;
                        }
                        break;
                    case 'G': if (Amount <= Gold) {
                            Gold -= Amount;
                        } else {
                            Message.SendText(0, Bot.Token, "you dont have enough money :(");
                            PoorFlag = true;
                        }
                        break;
                    case 'O': if (Amount <= Oil) {
                            Oil -= Amount;
                        } else {
                            Message.SendText(0, Bot.Token, "you dont have enough money :(");
                            PoorFlag = true;
                        }
                        break;
                    case 'R': if (Amount <= Ore) {
                            Ore -= Amount;
                        } else {
                            Message.SendText(0, Bot.Token, "you dont have enough money :(");
                        }
                        break;
                    case 'U': if (Amount <= Uranium) {
                            Uranium -= Amount;
                        } else {
                            Message.SendText(0, Bot.Token, "you dont have enough money :(");
                            PoorFlag = true;
                        }
                        break;
                    case 'D': if (Amount <= Diamonds) {
                            Diamonds -= Amount;
                        } else {
                            Message.SendText(0, Bot.Token, "you dont have enough money :(");
                            PoorFlag = true;
                        }
                        break;
                }

                if (!PoorFlag) {
                    std::ostringstream Text;
                    Text << "Withdrawing " << Amount << " " << out[1] << " from user " << UserName;
                    Message.SendText(0, Bot.Token, Text.str());
                }
            }
            DBWrite << UserName << " " << UserID << " " << Money << " " << Gold << " " << Oil << " " << Ore << " " << Uranium << " " << Diamonds << "\n";
        }
    }

    if (!UserFlag) {
        Message.SendText(0, Bot.Token, "mentioned user does not exist");
    }

    DBWrite.close();
    DBRead.close();

    std::rename("TradeDB.txt", "TradeDB.TMP");
    std::rename("Temp.txt", "TradeDB.txt");
    std::remove("TradeDB.TMP");
    return 0;
}

int Deposit(Message& Message, Bot& Bot) {

    // /withdraw user type amount
    const char delim = ' ';
    std::vector<std::string> out;
    tokenize(Message.Data.Text, delim, out);

    if (out.size() != 3) {
        Message.TextReply(0, Bot.Token, "usage: \n\n/deposit Type amount\nresource: (M - Money, G - Gold, O - Oil, R - Ore, U - Uranium, D - Diamonds)");
        return 1;
    }

    std::ifstream DBRead("TradeDB.txt");
    std::string Line;
    std::ofstream DBWrite;

    DBWrite.open("Temp.txt", std::ofstream::app);
    //Database << out[1].c_str() << " " << out[2].c_str() << " 0 0 0 0 0 0 \n";

    std::string UserName, UserID;
    long long int Money, Gold, Oil, Ore, Uranium, Diamonds;

    std::string User = "@";
    User.append(Message.Data.UserName);

    bool UserFlag = false;
    while (std::getline(DBRead, Line)) {
        if (Line.substr(0, Line.find(" ")) == User) {
            long long int Amount;
            try {
                //shits not workin
                Amount = std::stoll(out[2]);
            }
            catch (...) {
                Amount = 0;
            }
            std::istringstream iss(Line);
            if (!(iss >> UserName >> UserID >> Money >> Gold >> Oil >> Ore >> Uranium >> Diamonds)) { break; }

            if (UserName == User) {

                UserFlag = true;
                switch (out[1][0]) {
                    case 'M':
                        Money += Amount;
                        break;
                    case 'G':
                            Gold += Amount;
                        break;
                    case 'O':
                            Oil += Amount;
                        break;
                    case 'R':
                            Ore += Amount;
                        break;
                    case 'U':
                            Uranium += Amount;
                        break;
                    case 'D':
                            Diamonds += Amount;
                        break;
                }

                std::ostringstream Text;
                Text << "adding " << Amount << " " << out[1] << " from user " << UserName;
                Message.SendText(0, Bot.Token, Text.str());

            }
            DBWrite << UserName << " " << UserID << " " << Money << " " << Gold << " " << Oil << " " << Ore << " " << Uranium << " " << Diamonds << "\n";
        }
    }

    if (!UserFlag) {
        Message.SendText(0, Bot.Token, "mentioned user does not exist");
    }

    DBWrite.close();
    DBRead.close();

    std::rename("TradeDB.txt", "TradeDB.TMP");
    std::rename("Temp.txt", "TradeDB.txt");
    std::remove("TradeDB.TMP");
    return 0;
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
    long long int Money, Gold, Oil, Ore, Uranium, Diamonds;
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
