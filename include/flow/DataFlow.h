//---------------------------------------------------------------------------------------------------------------------
//  FLOW
//---------------------------------------------------------------------------------------------------------------------
//  Copyright 2019 Pablo Ramon Soria (a.k.a. Bardo91) pabramsor@gmail.com
//---------------------------------------------------------------------------------------------------------------------
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
//  and associated documentation files (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge, publish, distribute,
//  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial
//  portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
//  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//---------------------------------------------------------------------------------------------------------------------


#ifndef FLOW_DATAFLOW_H_
#define FLOW_DATAFLOW_H_

#include <vector>
#include <cstdlib>

#include <any>
#include <functional>
#include <map>

namespace flow{
        
    class DataFlow{
    public:
        DataFlow(std::vector<std::pair<std::string, std::string>> _flows, std::function<void(DataFlow _f)> _callback);

        void update(std::string _tag, std::any _data);

        void checkData();

        template<typename T_>
        T_ get(std::string _tag);

        std::map<std::string, std::string>  types_;
        std::map<std::string, std::any>     data_;
        std::map<std::string, bool>         updated_;
        std::function<void(DataFlow _f)> callback_;
    };
}


#define FLOW_TYPE_REGISTER(tagType_, Type_)                                                     \
    namespace flow{                                                                             \
        template<>                                                                              \
        Type_ DataFlow::get<Type_>(std::string _tag){                                           \
            if(types_.find(_tag) == types_.end() || types_[_tag] != tagType_ ){                 \
                throw std::invalid_argument("Bad tag type when getting data from DataFlow");    \
            }                                                                                   \
            return std::any_cast<Type_>(data_[_tag]);                                           \
        }                                                                                       \
    }                                                                                           \

#endif