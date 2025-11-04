#ifndef PRODUCTREQUEST_H
#define PRODUCTREQUEST_H

#include <string>
#include <vector>

struct ProductRequest {
    std::vector<std::string> plantNames;
    bool wantsWrapping = false;
    bool wantsCard = false;
    std::string cardMessage = "";
};

#endif
