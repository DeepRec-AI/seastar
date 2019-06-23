
#line 1 "http/request_parser.rl"
/*
 * This file is open source software, licensed to you under the terms
 * of the Apache License, Version 2.0 (the "License").  See the NOTICE file
 * distributed with this work for additional information regarding copyright
 * ownership.  You may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 */

#pragma once

#include "core/ragel.hh"
#include <memory>
#include <unordered_map>
#include "http/request.hh"

namespace seastar {

using namespace httpd;


#line 34 "http/request_parser.rl"


#line 99 "http/request_parser.rl"


class http_request_parser : public ragel_parser_base<http_request_parser> {
    
#line 45 "build/release/gen/http/request_parser.hh"
static const int start = 1;
static const int error = 0;

static const int en_main = 1;


#line 103 "http/request_parser.rl"
public:
    enum class state {
        error,
        eof,
        done,
    };
    std::unique_ptr<httpd::request> _req;
    sstring _field_name;
    sstring _value;
    state _state;
public:
    void init() {
        init_base();
        _req.reset(new httpd::request());
        _state = state::eof;
        
#line 69 "build/release/gen/http/request_parser.hh"
	{
	 _fsm_cs = start;
	}

#line 119 "http/request_parser.rl"
    }
    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        bool done = false;
        if (p != pe) {
            _state = state::error;
        }
        
#line 84 "build/release/gen/http/request_parser.hh"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  _fsm_cs )
	{
case 1:
	if ( 65 <= (*p) && (*p) <= 90 )
		goto tr0;
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
tr0:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 107 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 32 )
		goto tr2;
	if ( 65 <= (*p) && (*p) <= 90 )
		goto st2;
	goto st0;
tr2:
#line 43 "http/request_parser.rl"
	{
    _req->_method = str();
}
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 123 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 13: goto tr5;
		case 32: goto st0;
	}
	goto tr4;
tr4:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 139 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 13: goto st5;
		case 32: goto tr8;
	}
	goto st4;
tr5:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 155 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 10: goto st0;
		case 13: goto st5;
		case 32: goto tr8;
	}
	goto st4;
tr8:
#line 47 "http/request_parser.rl"
	{
    _req->_url = str();
}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 172 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 72 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	if ( (*p) == 84 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 84 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 80 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 47 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr14;
	goto st0;
tr14:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 221 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 46 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 13 )
		goto tr17;
	goto st0;
tr17:
#line 51 "http/request_parser.rl"
	{
    _req->_version = str();
}
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 249 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 10 )
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 13: goto st17;
		case 33: goto tr20;
		case 124: goto tr20;
		case 126: goto tr20;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr20;
		} else if ( (*p) >= 35 )
			goto tr20;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr20;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr20;
		} else
			goto tr20;
	} else
		goto tr20;
	goto st0;
tr34:
#line 63 "http/request_parser.rl"
	{
    _req->_headers[_field_name] = std::move(_value);
}
	goto st17;
tr44:
#line 67 "http/request_parser.rl"
	{
    _req->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st17;
tr59:
#line 63 "http/request_parser.rl"
	{
    _req->_headers[_field_name] = std::move(_value);
}
#line 67 "http/request_parser.rl"
	{
    _req->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 307 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 10 )
		goto tr21;
	goto st0;
tr21:
#line 71 "http/request_parser.rl"
	{
    done = true;
    {p++;  _fsm_cs = 34; goto _out;}
}
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 322 "build/release/gen/http/request_parser.hh"
	goto st0;
tr20:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
tr35:
#line 63 "http/request_parser.rl"
	{
    _req->_headers[_field_name] = std::move(_value);
}
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 344 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr22;
		case 32: goto tr22;
		case 33: goto st18;
		case 58: goto tr24;
		case 124: goto st18;
		case 126: goto st18;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st18;
		} else if ( (*p) >= 35 )
			goto st18;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st18;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st18;
		} else
			goto st18;
	} else
		goto st18;
	goto st0;
tr22:
#line 55 "http/request_parser.rl"
	{
    _field_name = str();
}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 381 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto st19;
		case 32: goto st19;
		case 58: goto st20;
	}
	goto st0;
tr28:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st20;
tr24:
#line 55 "http/request_parser.rl"
	{
    _field_name = str();
}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 404 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr28;
		case 13: goto tr29;
		case 32: goto tr28;
	}
	goto tr27;
tr27:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 421 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 13 )
		goto tr31;
	goto st21;
tr29:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st22;
tr31:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 445 "build/release/gen/http/request_parser.hh"
	if ( (*p) == 10 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 9: goto tr33;
		case 13: goto tr34;
		case 32: goto tr33;
		case 33: goto tr35;
		case 124: goto tr35;
		case 126: goto tr35;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr35;
		} else if ( (*p) >= 35 )
			goto tr35;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr35;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr35;
		} else
			goto tr35;
	} else
		goto tr35;
	goto st0;
tr37:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st24;
tr33:
#line 63 "http/request_parser.rl"
	{
    _req->_headers[_field_name] = std::move(_value);
}
	goto st24;
tr43:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
#line 67 "http/request_parser.rl"
	{
    _req->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st24;
tr58:
#line 63 "http/request_parser.rl"
	{
    _req->_headers[_field_name] = std::move(_value);
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
#line 67 "http/request_parser.rl"
	{
    _req->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 523 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr37;
		case 13: goto tr38;
		case 32: goto tr37;
	}
	goto tr36;
tr36:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st25;
tr40:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 546 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr40;
		case 13: goto tr41;
		case 32: goto tr40;
	}
	goto st25;
tr38:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st26;
tr41:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 573 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr40;
		case 10: goto st27;
		case 13: goto tr41;
		case 32: goto tr40;
	}
	goto st25;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 9: goto tr43;
		case 13: goto tr44;
		case 32: goto tr43;
		case 33: goto tr45;
		case 124: goto tr45;
		case 126: goto tr45;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr45;
		} else if ( (*p) >= 35 )
			goto tr45;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr45;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr45;
		} else
			goto tr45;
	} else
		goto tr45;
	goto st25;
tr45:
#line 67 "http/request_parser.rl"
	{
    _req->_headers[_field_name] += sstring(" ") + std::move(_value);
}
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st28;
tr60:
#line 63 "http/request_parser.rl"
	{
    _req->_headers[_field_name] = std::move(_value);
}
#line 67 "http/request_parser.rl"
	{
    _req->_headers[_field_name] += sstring(" ") + std::move(_value);
}
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 639 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr46;
		case 13: goto tr41;
		case 32: goto tr46;
		case 33: goto st28;
		case 58: goto tr48;
		case 124: goto st28;
		case 126: goto st28;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto st28;
		} else if ( (*p) >= 35 )
			goto st28;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto st28;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto st28;
		} else
			goto st28;
	} else
		goto st28;
	goto st25;
tr49:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st29;
tr46:
#line 55 "http/request_parser.rl"
	{
    _field_name = str();
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 687 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr49;
		case 13: goto tr41;
		case 32: goto tr49;
		case 58: goto st30;
	}
	goto st25;
tr48:
#line 55 "http/request_parser.rl"
	{
    _field_name = str();
}
	goto st30;
tr52:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 715 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr52;
		case 13: goto tr53;
		case 32: goto tr52;
	}
	goto tr51;
tr51:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
	goto st31;
tr55:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 738 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr55;
		case 13: goto tr56;
		case 32: goto tr55;
	}
	goto st31;
tr53:
#line 39 "http/request_parser.rl"
	{
    g.mark_start(p);
}
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st32;
tr56:
#line 59 "http/request_parser.rl"
	{
    _value = str();
}
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 765 "build/release/gen/http/request_parser.hh"
	switch( (*p) ) {
		case 9: goto tr40;
		case 10: goto st33;
		case 13: goto tr41;
		case 32: goto tr40;
	}
	goto st25;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 9: goto tr58;
		case 13: goto tr59;
		case 32: goto tr58;
		case 33: goto tr60;
		case 124: goto tr60;
		case 126: goto tr60;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr60;
		} else if ( (*p) >= 35 )
			goto tr60;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr60;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr60;
		} else
			goto tr60;
	} else
		goto tr60;
	goto st25;
	}
	_test_eof2:  _fsm_cs = 2; goto _test_eof; 
	_test_eof3:  _fsm_cs = 3; goto _test_eof; 
	_test_eof4:  _fsm_cs = 4; goto _test_eof; 
	_test_eof5:  _fsm_cs = 5; goto _test_eof; 
	_test_eof6:  _fsm_cs = 6; goto _test_eof; 
	_test_eof7:  _fsm_cs = 7; goto _test_eof; 
	_test_eof8:  _fsm_cs = 8; goto _test_eof; 
	_test_eof9:  _fsm_cs = 9; goto _test_eof; 
	_test_eof10:  _fsm_cs = 10; goto _test_eof; 
	_test_eof11:  _fsm_cs = 11; goto _test_eof; 
	_test_eof12:  _fsm_cs = 12; goto _test_eof; 
	_test_eof13:  _fsm_cs = 13; goto _test_eof; 
	_test_eof14:  _fsm_cs = 14; goto _test_eof; 
	_test_eof15:  _fsm_cs = 15; goto _test_eof; 
	_test_eof16:  _fsm_cs = 16; goto _test_eof; 
	_test_eof17:  _fsm_cs = 17; goto _test_eof; 
	_test_eof34:  _fsm_cs = 34; goto _test_eof; 
	_test_eof18:  _fsm_cs = 18; goto _test_eof; 
	_test_eof19:  _fsm_cs = 19; goto _test_eof; 
	_test_eof20:  _fsm_cs = 20; goto _test_eof; 
	_test_eof21:  _fsm_cs = 21; goto _test_eof; 
	_test_eof22:  _fsm_cs = 22; goto _test_eof; 
	_test_eof23:  _fsm_cs = 23; goto _test_eof; 
	_test_eof24:  _fsm_cs = 24; goto _test_eof; 
	_test_eof25:  _fsm_cs = 25; goto _test_eof; 
	_test_eof26:  _fsm_cs = 26; goto _test_eof; 
	_test_eof27:  _fsm_cs = 27; goto _test_eof; 
	_test_eof28:  _fsm_cs = 28; goto _test_eof; 
	_test_eof29:  _fsm_cs = 29; goto _test_eof; 
	_test_eof30:  _fsm_cs = 30; goto _test_eof; 
	_test_eof31:  _fsm_cs = 31; goto _test_eof; 
	_test_eof32:  _fsm_cs = 32; goto _test_eof; 
	_test_eof33:  _fsm_cs = 33; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 128 "http/request_parser.rl"
        if (!done) {
            p = nullptr;
        } else {
            _state = state::done;
        }
        return p;
    }
    auto get_parsed_request() {
        return std::move(_req);
    }
    bool eof() const {
        return _state == state::eof;
    }
};

}
