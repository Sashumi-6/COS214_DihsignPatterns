/**
 * @file productRequest.h
 * @brief Declares the data structure describing customer product requests.
 */
#ifndef PRODUCTREQUEST_H
#define PRODUCTREQUEST_H

#include <string>
#include <vector>

/**
 * @brief Represents a customer's request for a custom plant product.
 */
struct ProductRequest {
    /** Names of plants to include in the arrangement. */
    std::vector<std::string> plantNames;
    /** Indicates whether gift wrapping is requested. */
    bool wantsWrapping = false;
    /** Indicates whether a card should be included. */
    bool wantsCard = false;
    /** Message to print on the card when requested. */
    std::string cardMessage = "";
};

#endif
