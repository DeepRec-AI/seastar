
#line 1 "http/http_response_parser.rl"
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
 * Copyright (C) 2015 Cloudius Systems, Ltd.
 */

#include "core/ragel.hh"
#include <memory>
#include <unordered_map>

namespace seastar {

struct http_response {
    sstring _version;
    std::unordered_map<sstring, sstring> _headers;
};


#line 34 "http/http_response_parser.rl"


#line 89 "http/http_response_parser.rl"


class http_response_parser : public ragel_parser_base<http_response_parser> {
    
#line 45 "build/release/gen/http/http_response_parser.hh"
static const int start = 1;
static const int error = 0;

static const int en_main = 1;


#line 93 "http/http_response_parser.rl"
public:
    enum class state {
        error,
        eof,
        done,
    };
    std::unique_ptr<http_response> _rsp;
    sstring _field_name;
    sstring _value;
    state _state;
public:
    void init() {
        init_base();
        _rsp.reset(new http_response());
        _state = state::eof;
        
#line 69 "build/release/gen/http/http_response_parser.hh"
	{
	 _fsm_cs = start;
	}

#line 109 "http/http_response_parser.rl"
    }
    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        bool done = false;
        if (p != pe) {
            _state = state::error;
        }
        
#line 84 "build/release/gen/http/http_response_parser.hh"
	{
	if ( p == pe )
		goto _test_eof;
	switch (  _fsm_cs )
	{
case 1:
	if ( (*p) == 72 )
		goto st2;
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 84 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 84 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 80 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 47 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr6;
	goto st0;
tr6:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 142 "build/release/gen/http/http_response_parser.hh"
	if ( (*p) == 46 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	if ( (*p) == 32 )
		goto tr9;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto tr9;
	goto st0;
tr9:
#line 43 "http/http_response_parser.rl"
	{
    _rsp->_version = str();
}
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 172 "build/release/gen/http/http_response_parser.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( (*p) == 32 )
		goto st14;
	if ( 9 <= (*p) && (*p) <= 13 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	switch( (*p) ) {
		case 10: goto st0;
		case 13: goto st15;
	}
	goto st14;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 10 )
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
	switch( (*p) ) {
		case 13: goto st17;
		case 33: goto tr17;
		case 124: goto tr17;
		case 126: goto tr17;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr17;
		} else if ( (*p) >= 35 )
			goto tr17;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr17;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr17;
		} else
			goto tr17;
	} else
		goto tr17;
	goto st0;
tr30:
#line 55 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] = std::move(_value);
}
	goto st17;
tr40:
#line 59 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st17;
tr55:
#line 55 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] = std::move(_value);
}
#line 59 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 269 "build/release/gen/http/http_response_parser.hh"
	if ( (*p) == 10 )
		goto tr18;
	goto st0;
tr18:
#line 63 "http/http_response_parser.rl"
	{
    done = true;
    {p++;  _fsm_cs = 34; goto _out;}
}
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 284 "build/release/gen/http/http_response_parser.hh"
	goto st0;
tr17:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
tr31:
#line 55 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] = std::move(_value);
}
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 306 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr19;
		case 32: goto tr19;
		case 33: goto st18;
		case 58: goto tr21;
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
tr19:
#line 47 "http/http_response_parser.rl"
	{
    _field_name = str();
}
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 343 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto st19;
		case 32: goto st19;
		case 58: goto st20;
	}
	goto st0;
tr21:
#line 47 "http/http_response_parser.rl"
	{
    _field_name = str();
}
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 360 "build/release/gen/http/http_response_parser.hh"
	if ( (*p) == 13 )
		goto tr25;
	goto tr24;
tr24:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 374 "build/release/gen/http/http_response_parser.hh"
	if ( (*p) == 13 )
		goto tr27;
	goto st21;
tr25:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st22;
tr27:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 398 "build/release/gen/http/http_response_parser.hh"
	if ( (*p) == 10 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 9: goto tr29;
		case 13: goto tr30;
		case 32: goto tr29;
		case 33: goto tr31;
		case 124: goto tr31;
		case 126: goto tr31;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr31;
		} else if ( (*p) >= 35 )
			goto tr31;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr31;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr31;
		} else
			goto tr31;
	} else
		goto tr31;
	goto st0;
tr33:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st24;
tr29:
#line 55 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] = std::move(_value);
}
	goto st24;
tr39:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
#line 59 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st24;
tr54:
#line 55 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] = std::move(_value);
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
#line 59 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
	goto st24;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
#line 476 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr33;
		case 13: goto tr34;
		case 32: goto tr33;
	}
	goto tr32;
tr32:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st25;
tr36:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st25;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
#line 499 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr36;
		case 13: goto tr37;
		case 32: goto tr36;
	}
	goto st25;
tr34:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st26;
tr37:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st26;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
#line 526 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr36;
		case 10: goto st27;
		case 13: goto tr37;
		case 32: goto tr36;
	}
	goto st25;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	switch( (*p) ) {
		case 9: goto tr39;
		case 13: goto tr40;
		case 32: goto tr39;
		case 33: goto tr41;
		case 124: goto tr41;
		case 126: goto tr41;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr41;
		} else if ( (*p) >= 35 )
			goto tr41;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr41;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr41;
		} else
			goto tr41;
	} else
		goto tr41;
	goto st25;
tr41:
#line 59 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st28;
tr56:
#line 55 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] = std::move(_value);
}
#line 59 "http/http_response_parser.rl"
	{
    _rsp->_headers[_field_name] += sstring(" ") + std::move(_value);
}
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 592 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr42;
		case 13: goto tr37;
		case 32: goto tr42;
		case 33: goto st28;
		case 58: goto tr44;
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
tr45:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st29;
tr42:
#line 47 "http/http_response_parser.rl"
	{
    _field_name = str();
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 640 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr45;
		case 13: goto tr37;
		case 32: goto tr45;
		case 58: goto st30;
	}
	goto st25;
tr44:
#line 47 "http/http_response_parser.rl"
	{
    _field_name = str();
}
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 658 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr48;
		case 13: goto tr49;
		case 32: goto tr48;
	}
	goto tr47;
tr47:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
	goto st31;
tr48:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st31;
tr51:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 691 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr51;
		case 13: goto tr52;
		case 32: goto tr51;
	}
	goto st31;
tr49:
#line 39 "http/http_response_parser.rl"
	{
    g.mark_start(p);
}
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st32;
tr52:
#line 51 "http/http_response_parser.rl"
	{
    _value = str();
}
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 718 "build/release/gen/http/http_response_parser.hh"
	switch( (*p) ) {
		case 9: goto tr36;
		case 10: goto st33;
		case 13: goto tr37;
		case 32: goto tr36;
	}
	goto st25;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
	switch( (*p) ) {
		case 9: goto tr54;
		case 13: goto tr55;
		case 32: goto tr54;
		case 33: goto tr56;
		case 124: goto tr56;
		case 126: goto tr56;
	}
	if ( (*p) < 45 ) {
		if ( (*p) > 39 ) {
			if ( 42 <= (*p) && (*p) <= 43 )
				goto tr56;
		} else if ( (*p) >= 35 )
			goto tr56;
	} else if ( (*p) > 46 ) {
		if ( (*p) < 65 ) {
			if ( 48 <= (*p) && (*p) <= 57 )
				goto tr56;
		} else if ( (*p) > 90 ) {
			if ( 94 <= (*p) && (*p) <= 122 )
				goto tr56;
		} else
			goto tr56;
	} else
		goto tr56;
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

#line 118 "http/http_response_parser.rl"
        if (!done) {
            p = nullptr;
        } else {
            _state = state::done;
        }
        return p;
    }
    auto get_parsed_response() {
        return std::move(_rsp);
    }
    bool eof() const {
        return _state == state::eof;
    }
};

}
