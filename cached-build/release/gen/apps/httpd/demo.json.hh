/*
* Copyright (C) 2014 Cloudius Systems, Ltd.
*
* This work is open source software, licensed under the terms of the
* BSD license as described in the LICENSE f in the top-level directory.
*
*  This is an Auto-Generated-code  
*  Changes you do in this file will be erased on next code generation
*/

#ifndef __JSON_AUTO_GENERATED_demo_json
#define __JSON_AUTO_GENERATED_demo_json

#include "core/sstring.hh"
#include "json/json_elements.hh"
#include "http/json_path.hh"

#include <iostream>
#include <boost/range/irange.hpp>

namespace seastar {

namespace httpd {

namespace demo_json {

/**
 * Demonstrate an object
 */
struct my_object : public json::json_base {
    /**
     * Demonstrate an enum returned, note this is not the same enum type of the request
     */
  enum class my_object_enum_var {  VAL1,   VAL2,   VAL3, NUM_ITEMS};
  struct enum_var_wrapper : public json::jsonable  {
        enum_var_wrapper() = default;
        virtual std::string to_json() const {
            switch(v) {
              case my_object_enum_var::VAL1: return "\"VAL1\"";
      case my_object_enum_var::VAL2: return "\"VAL2\"";
      case my_object_enum_var::VAL3: return "\"VAL3\"";
      default: return "\"Unknown\"";
        }
     }
    template<class T>
    enum_var_wrapper (const T& _v) {
    switch(_v) {
          case T::VAL1: v = my_object_enum_var::VAL1; break;
      case T::VAL2: v = my_object_enum_var::VAL2; break;
      case T::VAL3: v = my_object_enum_var::VAL3; break;
      default: v = my_object_enum_var::NUM_ITEMS;
        }
    }
    template<class T>
    operator T() const {
        switch(v) {
          case my_object_enum_var::VAL1: return T::VAL1;
      case my_object_enum_var::VAL2: return T::VAL2;
      case my_object_enum_var::VAL3: return T::VAL3;
      default: return T::VAL1;
          }
        }
        typedef typename std::underlying_type<my_object_enum_var>::type pos_type;
        enum_var_wrapper& operator++() {
        v = static_cast<my_object_enum_var>(static_cast<pos_type>(v) + 1);
            return *this;
        }
        enum_var_wrapper & operator++(int) {
            return ++(*this);
        }
        bool operator==(const  enum_var_wrapper& c) const {
            return v == c.v;
        }
        bool operator!=(const enum_var_wrapper& c) const {
            return v != c.v;
        }
        bool operator<=(const enum_var_wrapper& c) const {
            return static_cast<pos_type>(v) <= static_cast<pos_type>(c.v);
        }
        static enum_var_wrapper begin() {
            return enum_var_wrapper (my_object_enum_var::VAL1);
        }
        static enum_var_wrapper end() {
            return enum_var_wrapper (my_object_enum_var::NUM_ITEMS);
        }
        static boost::integer_range<enum_var_wrapper> all_items() {
            return boost::irange(begin(), end());
        }
        my_object_enum_var v;
    };
    
  json::json_element<enum_var_wrapper> enum_var;

    /**
     * The first parameter in the path
     */
  json::json_element< sstring > var1;

    /**
     * The second parameter in the path
     */
  json::json_element< sstring > var2;

void register_params() {
  add(&enum_var,"enum_var");
  add(&var1,"var1");
  add(&var2,"var2");

}
my_object() {
  register_params();
}
my_object(const my_object & e) {
  register_params();
  enum_var = e.enum_var;
  var1 = e.var1;
  var2 = e.var2;

}
template<class T>
my_object& operator=(const T& e) {
  enum_var = e.enum_var;
  var1 = e.var1;
  var2 = e.var2;

  return *this;
}
my_object& operator=(const my_object& e) {
  enum_var = e.enum_var;
  var1 = e.var1;
  var2 = e.var2;

  return *this;
}
template<class T>
my_object& update(T& e) {
  e.enum_var = enum_var;
  e.var1 = var1;
  e.var2 = var2;

  return *this;
}
};


static const sstring name = "demo";
    /**
     * Returns the number of seconds since the system was booted
     */
static const path_description hello_world("/hello/world",GET,"hello_world",
{{"var1", false}
,{"var2", true}},{"query_enum"});
namespace ns_hello_world{
enum class query_enum {VAL1, VAL2, VAL3, NUM_ITEMS};
query_enum str2query_enum(const sstring& str) {
  static const sstring arr[] = {"VAL1","VAL2","VAL3"};
  int i;
  for (i=0; i < 3; i++) {
    if (arr[i] == str) {return (query_enum)i;}
}
  return (query_enum)i;
}
}

}
}
}
#endif //__JSON_AUTO_GENERATED_HEADERS
