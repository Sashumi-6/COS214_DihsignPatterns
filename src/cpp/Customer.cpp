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

RequestCommand Customer::createCustomerQuery()
{

    std::cout << "check!\n";

    int waterStrategy;
    int sunStrategy;

    AdviceCriteria a = AdviceCriteria();

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
            a.sunlight = SunlightPreference::LOW;
            a.water = WaterPreference::LOW;
        }
        else if (sunStrategy == 1)
        {
            std::cout << "Your recommended plant is a poppy!\n";
            a.sunlight = SunlightPreference::MEDIUM;
            a.water = WaterPreference::LOW;
        }
        else if (sunStrategy == 2)
        {
            std::cout << "Your recommended plant is a cactus!\n";
            a.sunlight = SunlightPreference::HIGH;
            a.water = WaterPreference::LOW;
        }
        else
        {

            std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                return;
        }
    }
    else if (waterStrategy == 1)
    {
        if (sunStrategy == 0)
        {
            std::cout << "Your recommended plant is a fern!\n";
            a.sunlight = SunlightPreference::LOW;
            a.water = WaterPreference::MEDIUM;
        }
        else if (sunStrategy == 1)
        {
            std::cout << "Your recommended plant is a spider plant!\n";
            a.sunlight = SunlightPreference::MEDIUM;
            a.water = WaterPreference::MEDIUM;
        }
        else if (sunStrategy == 2)
        {
            std::cout << "Your recommended plant is a gardenia!\n";
            a.sunlight = SunlightPreference::HIGH;
            a.water = WaterPreference::MEDIUM;
        }
        else
        {

            std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                return;
        }
    }

    else if (waterStrategy == 2)
    {
        if (sunStrategy == 0)
        {
            std::cout << "Your recommended plant is a lily of the valley!\n";
            a.sunlight = SunlightPreference::LOW;
            a.water = WaterPreference::HIGH;
        }
        else if (sunStrategy == 1)
        {
            std::cout << "Your recommended plant is a pussy willow!\n";
            a.sunlight = SunlightPreference::MEDIUM;
            a.water = WaterPreference::HIGH;
        }
        else if (sunStrategy == 2)
        {
            std::cout << "Your recommended plant is a basil!\n";
            a.sunlight = SunlightPreference::HIGH;
            a.water = WaterPreference::HIGH;
        }
        else
        {

            std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                return;
        }
    }
    else
    {

        std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
        return;
    }

    return RequestCommand(a);
}

Customer *Customer::createCustomerOrder()
{

    std::cout << "Here's the plant catalogue with ach plant's water and sun needs:\n";

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
            a.sunlight = SunlightPreference::LOW;
            a.water = WaterPreference::LOW;
        }
        else if (sunStrategy == 1)
        {
            std::cout << "Your recommended plant is a poppy!\n";
            a.sunlight = SunlightPreference::MEDIUM;
            a.water = WaterPreference::LOW;
        }
        else if (sunStrategy == 2)
        {
            std::cout << "Your recommended plant is a cactus!\n";
            a.sunlight = SunlightPreference::HIGH;
            a.water = WaterPreference::LOW;
        }
        else
        {

            std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                return;
        }
    }
    else if (waterStrategy == 1)
    {
        if (sunStrategy == 0)
        {
            std::cout << "Your recommended plant is a fern!\n";
            a.sunlight = SunlightPreference::LOW;
            a.water = WaterPreference::MEDIUM;
        }
        else if (sunStrategy == 1)
        {
            std::cout << "Your recommended plant is a spider plant!\n";
            a.sunlight = SunlightPreference::MEDIUM;
            a.water = WaterPreference::MEDIUM;
        }
        else if (sunStrategy == 2)
        {
            std::cout << "Your recommended plant is a gardenia!\n";
            a.sunlight = SunlightPreference::HIGH;
            a.water = WaterPreference::MEDIUM;
        }
        else
            {

            std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                return;
        }
    }

    else if (waterStrategy == 2)
    {
        if (sunStrategy == 0)
        {
            std::cout << "Your recommended plant is a lily of the valley!\n";
            a.sunlight = SunlightPreference::LOW;
            a.water = WaterPreference::HIGH;
        }
        else if (sunStrategy == 1)
        {
            std::cout << "Your recommended plant is a pussy willow!\n";
            a.sunlight = SunlightPreference::MEDIUM;
            a.water = WaterPreference::HIGH;
        }
        else if (sunStrategy == 2)
        {
            std::cout << "Your recommended plant is a basil!\n";
            a.sunlight = SunlightPreference::HIGH;
            a.water = WaterPreference::HIGH;
        }
        else
        {

            std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
                return;
        }
    }
    else
    {

        std::cout << "Not one of the number options, please choose again or cancel your request for assistance \n";
        return;
    }

    // Customer *Customer::createCustomerOrder(std::string message, bool wantsC, bool wantsW)
        ProductRequest customerOrder = ProductRequest();
        customerOrder.cardMessage = message;
        customerOrder.wantsCard = wantsC;
        customerOrder.wantsWrapping= wantsW;

    // std::vector<Plant*> plts = std::vector<Plant*>();

    // for(int i = 0; i < records.size(); i++){
    //     Plant toAdd = new Plant(records.element(i).name, )
    // }
}