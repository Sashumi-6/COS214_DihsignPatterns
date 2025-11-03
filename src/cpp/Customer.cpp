#include "../headers/Customer.h"
#include <iostream>

Customer::Customer()
{

    int option;
    bool stay = true;

    while (stay)
    {
        std::cout << "Welcome to Our Nursery, What Can We Help You With? Please pick from the following:\n";
        std::cout << "1. Place an order\n";
        std::cout << "2. Ask for assistance\n";
        std::cout << "Please enter the desired action's number below:\n";
        std::cin >> option;

        if (option == 1) // order
        {
            order = true;
            std::cout << "We're happy we could help! Would you like to continue shopping with us? Enter the following number for:\n";
            std::cout << "No : 0 \n";
            std::cout << "Yes : 1\n";

            std::cin >> stay;

            if (stay == 0)
            {
                
                std::cout << "Thank you for visiting, have a good day!\n";
            }
            else if (stay == 1)
            {
                std::cout << "Please choose another customer-action option to continue with us \n";
            }
        }

        else if (option == 2) // query assistance
        {
            
            order = false;

            createCustomerQuery();

            std::cout << "We're happy we could help! Would you like to continue shopping with us? Enter the following number for:\n";

            std::cout << "No : 0 \n";
            std::cout << "Yes : 1\n";

            std::cin >> stay;

            if (stay == 0)
            {
                
                std::cout << "Thank you for visiting, have a good day!\n";
            }
            else if (stay == 1)
            {
                std::cout << "Please choose another customer-action option to continue with us \n";
            }
        }

        else
        {
            std::cout << "That is not an allowed number option, would you like to continue shopping with us? Enter the following number for:\n";

            std::cout << "No : 0 \n";
            std::cout << "Yes : 1\n";

            std::cin >> stay;

            if (stay == 0)
            {
                std::cout << "Thank you for visiting, have a good day!\n";
            }
            else if (stay == 1)
            {
                std::cout << "Please choose another customer-action option to continue with us \n";
            }
        }
    }
    // if (customerType.equal("order"))
}

void Customer::createCustomerQuery()
{

    std::cout << "check!\n";

    int waterStrategy;
    int sunStrategy;
    bool exitLoop = false;
    bool exitInWater = false;


    
    do
    {

        std::cout << "Please Describe the Plant You are Looking For:\n";

        std::cout << "How much water does this plant need?\n";
        std::cout << "Low water: Enter 0\n";
        std::cout << "Medium water: Enter 1\n";
        std::cout << "High water: Enter 2\n";

        std::cin >> waterStrategy;

        std::cout << "How much sun does this plant need?\n";
        std::cout << "Low sun: Enter 0\n";
        std::cout << "Medium sun: Enter 1\n";
        std::cout << "High sun: Enter 2\n";

        std::cin >> sunStrategy;

        // water = 1 and low light is fern

        if (waterStrategy == 0)
        {
            if (sunStrategy == 0)
            {
                std::cout << "Your recommended plant is a hosta!\n";
            }
            else if (sunStrategy == 1)
            {
                std::cout << "Your recommended plant is a poppy!\n";
            }
            else if (sunStrategy == 2)
            {
                std::cout << "Your recommended plant is a cactus!\n";
            }
            else
            {

                std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                std::cout << "If you want to choose again, enter 1\n";
                std::cout << "If you want to cancel your request, enter 0\n";

                std::cin >> exitInWater;

                if (exitInWater == 1)
                {
                    exitLoop = true;
                }

                else
                {
                    return;
                }
            }
            exitLoop = false;
        }
        else if (waterStrategy == 1)
        {
            if (sunStrategy == 0)
            {
                std::cout << "Your recommended plant is a fern!\n";
            }
            else if (sunStrategy == 1)
            {
                std::cout << "Your recommended plant is a spider plant!\n";
            }
            else if (sunStrategy == 2)
            {
                std::cout << "Your recommended plant is a gardenia!\n";
            }
            else
            {

                std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                std::cout << "If you want to choose again, enter 1\n";
                std::cout << "If you want to cancel your request, enter 0\n";

                std::cin >> exitInWater;

                if (exitInWater == 1)
                {
                    exitLoop = true;
                }

                else
                {
                    return;
                }
            }
            exitLoop = false;
        }

        else if (waterStrategy == 2)
        {
            if (sunStrategy == 0)
            {
                std::cout << "Your recommended plant is a lily of the valley!\n";
            }
            else if (sunStrategy == 1)
            {
                std::cout << "Your recommended plant is a pussy willow!\n";
            }
            else if (sunStrategy == 2)
            {
                std::cout << "Your recommended plant is a basil!\n";
            }
            else
            {

                std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                std::cout << "If you want to choose again, enter 1\n";
                std::cout << "If you want to cancel your request, enter 0\n";

                std::cin >> exitInWater;

                if (exitInWater == 1)
                {
                    exitLoop = true;
                }

                else
                {
                    return;
                }
            }
            exitLoop = false;
        }
        else
            {

                std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                std::cout << "If you want to choose again, enter 1\n";
                std::cout << "If you want to cancel your request, enter 0\n";

                std::cin >> exitInWater;

                if (exitInWater == 1)
                {
                    exitLoop = true;
                }

                else
                {
                    return;
                }
        }
        exitLoop = false;
    }
    while (exitLoop);
}


Customer* Customer::createCustomerOrder(){


    
}