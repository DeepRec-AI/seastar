
#line 1 "apps/memcached/ascii.rl"
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

#include "core/ragel.hh"
#include "apps/memcached/memcached.hh"
#include <memory>
#include <algorithm>
#include <functional>

using namespace seastar;


#line 95 "apps/memcached/ascii.rl"


class memcache_ascii_parser : public ragel_parser_base<memcache_ascii_parser> {
    
#line 39 "build/release/gen/apps/memcached/ascii.hh"
static const int start = 1;
static const int error = 0;

static const int en_blob = 195;
static const int en_main = 1;


#line 99 "apps/memcached/ascii.rl"
public:
    enum class state {
        error,
        eof,
        cmd_set,
        cmd_cas,
        cmd_add,
        cmd_replace,
        cmd_get,
        cmd_gets,
        cmd_delete,
        cmd_flush_all,
        cmd_version,
        cmd_stats,
        cmd_stats_hash,
        cmd_incr,
        cmd_decr,
    };
    state _state;
    uint32_t _u32;
    uint64_t _u64;
    memcache::item_key _key;
    sstring _flags_str;
    uint32_t _expiration;
    uint32_t _size;
    sstring _size_str;
    uint32_t _size_left;
    uint64_t _version;
    sstring _blob;
    bool _noreply;
    std::vector<memcache::item_key> _keys;
public:
    void init() {
        init_base();
        _state = state::error;
        _keys.clear();
        
#line 85 "build/release/gen/apps/memcached/ascii.hh"
	{
	 _fsm_cs = start;
	 _fsm_top = 0;
	}

#line 136 "apps/memcached/ascii.rl"
    }

    char* parse(char* p, char* pe, char* eof) {
        sstring_builder::guard g(_builder, p, pe);
        auto str = [this, &g, &p] { g.mark_end(p); return get_str(); };
        
#line 98 "build/release/gen/apps/memcached/ascii.hh"
	{
	if ( p == pe )
		goto _test_eof;
	goto _resume;

_again:
	switch (  _fsm_cs ) {
		case 1: goto st1;
		case 0: goto st0;
		case 2: goto st2;
		case 3: goto st3;
		case 4: goto st4;
		case 5: goto st5;
		case 6: goto st6;
		case 7: goto st7;
		case 8: goto st8;
		case 9: goto st9;
		case 10: goto st10;
		case 11: goto st11;
		case 12: goto st12;
		case 13: goto st13;
		case 14: goto st14;
		case 15: goto st15;
		case 196: goto st196;
		case 16: goto st16;
		case 17: goto st17;
		case 18: goto st18;
		case 19: goto st19;
		case 20: goto st20;
		case 21: goto st21;
		case 22: goto st22;
		case 23: goto st23;
		case 24: goto st24;
		case 25: goto st25;
		case 26: goto st26;
		case 27: goto st27;
		case 28: goto st28;
		case 29: goto st29;
		case 30: goto st30;
		case 31: goto st31;
		case 32: goto st32;
		case 33: goto st33;
		case 34: goto st34;
		case 35: goto st35;
		case 36: goto st36;
		case 37: goto st37;
		case 38: goto st38;
		case 39: goto st39;
		case 40: goto st40;
		case 41: goto st41;
		case 42: goto st42;
		case 43: goto st43;
		case 44: goto st44;
		case 45: goto st45;
		case 46: goto st46;
		case 47: goto st47;
		case 48: goto st48;
		case 49: goto st49;
		case 50: goto st50;
		case 51: goto st51;
		case 52: goto st52;
		case 53: goto st53;
		case 54: goto st54;
		case 55: goto st55;
		case 56: goto st56;
		case 57: goto st57;
		case 58: goto st58;
		case 59: goto st59;
		case 60: goto st60;
		case 61: goto st61;
		case 62: goto st62;
		case 63: goto st63;
		case 64: goto st64;
		case 65: goto st65;
		case 66: goto st66;
		case 67: goto st67;
		case 68: goto st68;
		case 69: goto st69;
		case 70: goto st70;
		case 71: goto st71;
		case 197: goto st197;
		case 72: goto st72;
		case 73: goto st73;
		case 74: goto st74;
		case 75: goto st75;
		case 76: goto st76;
		case 77: goto st77;
		case 78: goto st78;
		case 79: goto st79;
		case 80: goto st80;
		case 81: goto st81;
		case 82: goto st82;
		case 83: goto st83;
		case 84: goto st84;
		case 85: goto st85;
		case 86: goto st86;
		case 87: goto st87;
		case 88: goto st88;
		case 89: goto st89;
		case 90: goto st90;
		case 91: goto st91;
		case 92: goto st92;
		case 93: goto st93;
		case 94: goto st94;
		case 95: goto st95;
		case 96: goto st96;
		case 97: goto st97;
		case 98: goto st98;
		case 99: goto st99;
		case 100: goto st100;
		case 101: goto st101;
		case 102: goto st102;
		case 103: goto st103;
		case 104: goto st104;
		case 105: goto st105;
		case 106: goto st106;
		case 198: goto st198;
		case 107: goto st107;
		case 108: goto st108;
		case 109: goto st109;
		case 110: goto st110;
		case 199: goto st199;
		case 111: goto st111;
		case 112: goto st112;
		case 113: goto st113;
		case 114: goto st114;
		case 115: goto st115;
		case 116: goto st116;
		case 117: goto st117;
		case 118: goto st118;
		case 119: goto st119;
		case 120: goto st120;
		case 121: goto st121;
		case 122: goto st122;
		case 123: goto st123;
		case 124: goto st124;
		case 125: goto st125;
		case 126: goto st126;
		case 127: goto st127;
		case 128: goto st128;
		case 129: goto st129;
		case 130: goto st130;
		case 131: goto st131;
		case 132: goto st132;
		case 133: goto st133;
		case 134: goto st134;
		case 135: goto st135;
		case 136: goto st136;
		case 137: goto st137;
		case 138: goto st138;
		case 139: goto st139;
		case 140: goto st140;
		case 141: goto st141;
		case 142: goto st142;
		case 143: goto st143;
		case 144: goto st144;
		case 145: goto st145;
		case 146: goto st146;
		case 147: goto st147;
		case 148: goto st148;
		case 149: goto st149;
		case 150: goto st150;
		case 151: goto st151;
		case 152: goto st152;
		case 153: goto st153;
		case 154: goto st154;
		case 155: goto st155;
		case 156: goto st156;
		case 157: goto st157;
		case 158: goto st158;
		case 159: goto st159;
		case 160: goto st160;
		case 161: goto st161;
		case 162: goto st162;
		case 163: goto st163;
		case 164: goto st164;
		case 165: goto st165;
		case 166: goto st166;
		case 167: goto st167;
		case 168: goto st168;
		case 169: goto st169;
		case 170: goto st170;
		case 171: goto st171;
		case 172: goto st172;
		case 173: goto st173;
		case 174: goto st174;
		case 175: goto st175;
		case 176: goto st176;
		case 177: goto st177;
		case 178: goto st178;
		case 179: goto st179;
		case 180: goto st180;
		case 181: goto st181;
		case 182: goto st182;
		case 183: goto st183;
		case 184: goto st184;
		case 185: goto st185;
		case 186: goto st186;
		case 187: goto st187;
		case 188: goto st188;
		case 189: goto st189;
		case 190: goto st190;
		case 191: goto st191;
		case 192: goto st192;
		case 193: goto st193;
		case 194: goto st194;
		case 195: goto st195;
		case 200: goto st200;
	default: break;
	}

	if ( ++p == pe )
		goto _test_eof;
_resume:
	switch (  _fsm_cs )
	{
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
	switch( (*p) ) {
		case 97: goto st2;
		case 99: goto st24;
		case 100: goto st48;
		case 102: goto st81;
		case 103: goto st101;
		case 105: goto st111;
		case 114: goto st128;
		case 115: goto st154;
		case 118: goto st187;
	}
	goto st0;
st0:
 _fsm_cs = 0;
	goto _out;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
	if ( (*p) == 100 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 100 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	if ( (*p) == 32 )
		goto st5;
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	if ( (*p) == 32 )
		goto st0;
	goto tr13;
tr13:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 372 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr15;
	goto st6;
tr15:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 384 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr16;
	goto st0;
tr16:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 398 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr17;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st8;
	goto st0;
tr17:
#line 62 "apps/memcached/ascii.rl"
	{ _flags_str = str(); }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 412 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr19;
	goto st0;
tr19:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st10;
tr21:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 430 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr20;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr21;
	goto st0;
tr20:
#line 63 "apps/memcached/ascii.rl"
	{ _expiration = _u32; }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 444 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr22;
	goto st0;
tr25:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st12;
tr22:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 466 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr23;
		case 32: goto tr24;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr25;
	goto st0;
tr23:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 484 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr26;
	goto st0;
tr26:
#line 70 "apps/memcached/ascii.rl"
	{ {
    prepush();
{ _fsm_stack[ _fsm_top++] = 14;goto st195;}} }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 498 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 10 )
		goto tr28;
	goto st0;
tr28:
#line 72 "apps/memcached/ascii.rl"
	{ _state = state::cmd_add; }
	goto st196;
tr58:
#line 74 "apps/memcached/ascii.rl"
	{ _state = state::cmd_cas; }
	goto st196;
tr79:
#line 83 "apps/memcached/ascii.rl"
	{ _state = state::cmd_decr; }
	goto st196;
tr105:
#line 77 "apps/memcached/ascii.rl"
	{ _state = state::cmd_delete; }
	goto st196;
tr116:
#line 78 "apps/memcached/ascii.rl"
	{ _state = state::cmd_flush_all; }
	goto st196;
tr155:
#line 82 "apps/memcached/ascii.rl"
	{ _state = state::cmd_incr; }
	goto st196;
tr186:
#line 73 "apps/memcached/ascii.rl"
	{ _state = state::cmd_replace; }
	goto st196;
tr214:
#line 71 "apps/memcached/ascii.rl"
	{ _state = state::cmd_set; }
	goto st196;
tr228:
#line 80 "apps/memcached/ascii.rl"
	{ _state = state::cmd_stats; }
	goto st196;
tr234:
#line 81 "apps/memcached/ascii.rl"
	{ _state = state::cmd_stats_hash; }
	goto st196;
tr242:
#line 79 "apps/memcached/ascii.rl"
	{ _state = state::cmd_version; }
	goto st196;
st196:
	if ( ++p == pe )
		goto _test_eof196;
case 196:
#line 557 "build/release/gen/apps/memcached/ascii.hh"
	goto st0;
tr24:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 569 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st17;
	goto st0;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
	if ( (*p) == 111 )
		goto st18;
	goto st0;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
	if ( (*p) == 114 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
	if ( (*p) == 101 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
	if ( (*p) == 112 )
		goto st21;
	goto st0;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
	if ( (*p) == 108 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
	if ( (*p) == 121 )
		goto tr35;
	goto st0;
tr35:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st23;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
#line 623 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st13;
	goto st0;
st24:
	if ( ++p == pe )
		goto _test_eof24;
case 24:
	if ( (*p) == 97 )
		goto st25;
	goto st0;
st25:
	if ( ++p == pe )
		goto _test_eof25;
case 25:
	if ( (*p) == 115 )
		goto st26;
	goto st0;
st26:
	if ( ++p == pe )
		goto _test_eof26;
case 26:
	if ( (*p) == 32 )
		goto st27;
	goto st0;
st27:
	if ( ++p == pe )
		goto _test_eof27;
case 27:
	if ( (*p) == 32 )
		goto st0;
	goto tr40;
tr40:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st28;
st28:
	if ( ++p == pe )
		goto _test_eof28;
case 28:
#line 665 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr42;
	goto st28;
tr42:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
	goto st29;
st29:
	if ( ++p == pe )
		goto _test_eof29;
case 29:
#line 677 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr43;
	goto st0;
tr43:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st30;
st30:
	if ( ++p == pe )
		goto _test_eof30;
case 30:
#line 691 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr44;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st30;
	goto st0;
tr44:
#line 62 "apps/memcached/ascii.rl"
	{ _flags_str = str(); }
	goto st31;
st31:
	if ( ++p == pe )
		goto _test_eof31;
case 31:
#line 705 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr46;
	goto st0;
tr46:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st32;
tr48:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st32;
st32:
	if ( ++p == pe )
		goto _test_eof32;
case 32:
#line 723 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr47;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr48;
	goto st0;
tr47:
#line 63 "apps/memcached/ascii.rl"
	{ _expiration = _u32; }
	goto st33;
st33:
	if ( ++p == pe )
		goto _test_eof33;
case 33:
#line 737 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr49;
	goto st0;
tr51:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st34;
tr49:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st34;
st34:
	if ( ++p == pe )
		goto _test_eof34;
case 34:
#line 759 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr50;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr51;
	goto st0;
tr50:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
	goto st35;
st35:
	if ( ++p == pe )
		goto _test_eof35;
case 35:
#line 773 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr52;
	goto st0;
tr52:
#line 60 "apps/memcached/ascii.rl"
	{ _u64 = 0; }
#line 60 "apps/memcached/ascii.rl"
	{ _u64 *= 10; _u64 += (*p) - '0'; }
	goto st36;
tr55:
#line 60 "apps/memcached/ascii.rl"
	{ _u64 *= 10; _u64 += (*p) - '0'; }
	goto st36;
st36:
	if ( ++p == pe )
		goto _test_eof36;
case 36:
#line 791 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr53;
		case 32: goto tr54;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr55;
	goto st0;
tr53:
#line 68 "apps/memcached/ascii.rl"
	{ _version = _u64; }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st37;
st37:
	if ( ++p == pe )
		goto _test_eof37;
case 37:
#line 809 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr56;
	goto st0;
tr56:
#line 74 "apps/memcached/ascii.rl"
	{ {
    prepush();
{ _fsm_stack[ _fsm_top++] = 38;goto st195;}} }
	goto st38;
st38:
	if ( ++p == pe )
		goto _test_eof38;
case 38:
#line 823 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _test_eof39;
case 39:
	if ( (*p) == 10 )
		goto tr58;
	goto st0;
tr54:
#line 68 "apps/memcached/ascii.rl"
	{ _version = _u64; }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st40;
st40:
	if ( ++p == pe )
		goto _test_eof40;
case 40:
#line 844 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st41;
	goto st0;
st41:
	if ( ++p == pe )
		goto _test_eof41;
case 41:
	if ( (*p) == 111 )
		goto st42;
	goto st0;
st42:
	if ( ++p == pe )
		goto _test_eof42;
case 42:
	if ( (*p) == 114 )
		goto st43;
	goto st0;
st43:
	if ( ++p == pe )
		goto _test_eof43;
case 43:
	if ( (*p) == 101 )
		goto st44;
	goto st0;
st44:
	if ( ++p == pe )
		goto _test_eof44;
case 44:
	if ( (*p) == 112 )
		goto st45;
	goto st0;
st45:
	if ( ++p == pe )
		goto _test_eof45;
case 45:
	if ( (*p) == 108 )
		goto st46;
	goto st0;
st46:
	if ( ++p == pe )
		goto _test_eof46;
case 46:
	if ( (*p) == 121 )
		goto tr65;
	goto st0;
tr65:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st47;
st47:
	if ( ++p == pe )
		goto _test_eof47;
case 47:
#line 898 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st37;
	goto st0;
st48:
	if ( ++p == pe )
		goto _test_eof48;
case 48:
	if ( (*p) == 101 )
		goto st49;
	goto st0;
st49:
	if ( ++p == pe )
		goto _test_eof49;
case 49:
	switch( (*p) ) {
		case 99: goto st50;
		case 108: goto st65;
	}
	goto st0;
st50:
	if ( ++p == pe )
		goto _test_eof50;
case 50:
	if ( (*p) == 114 )
		goto st51;
	goto st0;
st51:
	if ( ++p == pe )
		goto _test_eof51;
case 51:
	if ( (*p) == 32 )
		goto st52;
	goto st0;
st52:
	if ( ++p == pe )
		goto _test_eof52;
case 52:
	if ( (*p) == 32 )
		goto st0;
	goto tr72;
tr72:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st53;
st53:
	if ( ++p == pe )
		goto _test_eof53;
case 53:
#line 949 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr74;
	goto st53;
tr74:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
	goto st54;
st54:
	if ( ++p == pe )
		goto _test_eof54;
case 54:
#line 961 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr75;
	goto st0;
tr75:
#line 60 "apps/memcached/ascii.rl"
	{ _u64 = 0; }
#line 60 "apps/memcached/ascii.rl"
	{ _u64 *= 10; _u64 += (*p) - '0'; }
	goto st55;
tr78:
#line 60 "apps/memcached/ascii.rl"
	{ _u64 *= 10; _u64 += (*p) - '0'; }
	goto st55;
st55:
	if ( ++p == pe )
		goto _test_eof55;
case 55:
#line 979 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr76;
		case 32: goto tr77;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr78;
	goto st0;
tr76:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st56;
st56:
	if ( ++p == pe )
		goto _test_eof56;
case 56:
#line 995 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr79;
	goto st0;
tr77:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st57;
st57:
	if ( ++p == pe )
		goto _test_eof57;
case 57:
#line 1007 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _test_eof58;
case 58:
	if ( (*p) == 111 )
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _test_eof59;
case 59:
	if ( (*p) == 114 )
		goto st60;
	goto st0;
st60:
	if ( ++p == pe )
		goto _test_eof60;
case 60:
	if ( (*p) == 101 )
		goto st61;
	goto st0;
st61:
	if ( ++p == pe )
		goto _test_eof61;
case 61:
	if ( (*p) == 112 )
		goto st62;
	goto st0;
st62:
	if ( ++p == pe )
		goto _test_eof62;
case 62:
	if ( (*p) == 108 )
		goto st63;
	goto st0;
st63:
	if ( ++p == pe )
		goto _test_eof63;
case 63:
	if ( (*p) == 121 )
		goto tr86;
	goto st0;
tr86:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st64;
st64:
	if ( ++p == pe )
		goto _test_eof64;
case 64:
#line 1061 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st56;
	goto st0;
st65:
	if ( ++p == pe )
		goto _test_eof65;
case 65:
	if ( (*p) == 101 )
		goto st66;
	goto st0;
st66:
	if ( ++p == pe )
		goto _test_eof66;
case 66:
	if ( (*p) == 116 )
		goto st67;
	goto st0;
st67:
	if ( ++p == pe )
		goto _test_eof67;
case 67:
	if ( (*p) == 101 )
		goto st68;
	goto st0;
st68:
	if ( ++p == pe )
		goto _test_eof68;
case 68:
	if ( (*p) == 32 )
		goto st69;
	goto st0;
st69:
	if ( ++p == pe )
		goto _test_eof69;
case 69:
	if ( (*p) == 32 )
		goto st0;
	goto tr92;
tr92:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st70;
st70:
	if ( ++p == pe )
		goto _test_eof70;
case 70:
#line 1110 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr94;
		case 32: goto tr95;
	}
	goto st70;
tr94:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st71;
st71:
	if ( ++p == pe )
		goto _test_eof71;
case 71:
#line 1126 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 10: goto tr96;
		case 13: goto tr94;
		case 32: goto tr95;
	}
	goto st70;
tr96:
#line 77 "apps/memcached/ascii.rl"
	{ _state = state::cmd_delete; }
	goto st197;
st197:
	if ( ++p == pe )
		goto _test_eof197;
case 197:
#line 1141 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr94;
		case 32: goto tr95;
	}
	goto st70;
tr95:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st72;
st72:
	if ( ++p == pe )
		goto _test_eof72;
case 72:
#line 1157 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st73;
	goto st0;
st73:
	if ( ++p == pe )
		goto _test_eof73;
case 73:
	if ( (*p) == 111 )
		goto st74;
	goto st0;
st74:
	if ( ++p == pe )
		goto _test_eof74;
case 74:
	if ( (*p) == 114 )
		goto st75;
	goto st0;
st75:
	if ( ++p == pe )
		goto _test_eof75;
case 75:
	if ( (*p) == 101 )
		goto st76;
	goto st0;
st76:
	if ( ++p == pe )
		goto _test_eof76;
case 76:
	if ( (*p) == 112 )
		goto st77;
	goto st0;
st77:
	if ( ++p == pe )
		goto _test_eof77;
case 77:
	if ( (*p) == 108 )
		goto st78;
	goto st0;
st78:
	if ( ++p == pe )
		goto _test_eof78;
case 78:
	if ( (*p) == 121 )
		goto tr103;
	goto st0;
tr103:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st79;
st79:
	if ( ++p == pe )
		goto _test_eof79;
case 79:
#line 1211 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st80;
	goto st0;
st80:
	if ( ++p == pe )
		goto _test_eof80;
case 80:
	if ( (*p) == 10 )
		goto tr105;
	goto st0;
st81:
	if ( ++p == pe )
		goto _test_eof81;
case 81:
	if ( (*p) == 108 )
		goto st82;
	goto st0;
st82:
	if ( ++p == pe )
		goto _test_eof82;
case 82:
	if ( (*p) == 117 )
		goto st83;
	goto st0;
st83:
	if ( ++p == pe )
		goto _test_eof83;
case 83:
	if ( (*p) == 115 )
		goto st84;
	goto st0;
st84:
	if ( ++p == pe )
		goto _test_eof84;
case 84:
	if ( (*p) == 104 )
		goto st85;
	goto st0;
st85:
	if ( ++p == pe )
		goto _test_eof85;
case 85:
	if ( (*p) == 95 )
		goto st86;
	goto st0;
st86:
	if ( ++p == pe )
		goto _test_eof86;
case 86:
	if ( (*p) == 97 )
		goto st87;
	goto st0;
st87:
	if ( ++p == pe )
		goto _test_eof87;
case 87:
	if ( (*p) == 108 )
		goto st88;
	goto st0;
st88:
	if ( ++p == pe )
		goto _test_eof88;
case 88:
	if ( (*p) == 108 )
		goto st89;
	goto st0;
st89:
	if ( ++p == pe )
		goto _test_eof89;
case 89:
	switch( (*p) ) {
		case 13: goto tr114;
		case 32: goto tr115;
	}
	goto st0;
tr114:
#line 67 "apps/memcached/ascii.rl"
	{ _expiration = 0; }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st90;
tr119:
#line 63 "apps/memcached/ascii.rl"
	{ _expiration = _u32; }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st90;
st90:
	if ( ++p == pe )
		goto _test_eof90;
case 90:
#line 1303 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr116;
	goto st0;
tr115:
#line 67 "apps/memcached/ascii.rl"
	{ _expiration = 0; }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st91;
st91:
	if ( ++p == pe )
		goto _test_eof91;
case 91:
#line 1317 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st94;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr117;
	goto st0;
tr117:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st92;
tr121:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st92;
st92:
	if ( ++p == pe )
		goto _test_eof92;
case 92:
#line 1337 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr119;
		case 32: goto tr120;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr121;
	goto st0;
tr120:
#line 63 "apps/memcached/ascii.rl"
	{ _expiration = _u32; }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st93;
st93:
	if ( ++p == pe )
		goto _test_eof93;
case 93:
#line 1355 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _test_eof94;
case 94:
	if ( (*p) == 111 )
		goto st95;
	goto st0;
st95:
	if ( ++p == pe )
		goto _test_eof95;
case 95:
	if ( (*p) == 114 )
		goto st96;
	goto st0;
st96:
	if ( ++p == pe )
		goto _test_eof96;
case 96:
	if ( (*p) == 101 )
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _test_eof97;
case 97:
	if ( (*p) == 112 )
		goto st98;
	goto st0;
st98:
	if ( ++p == pe )
		goto _test_eof98;
case 98:
	if ( (*p) == 108 )
		goto st99;
	goto st0;
st99:
	if ( ++p == pe )
		goto _test_eof99;
case 99:
	if ( (*p) == 121 )
		goto tr127;
	goto st0;
tr127:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st100;
st100:
	if ( ++p == pe )
		goto _test_eof100;
case 100:
#line 1409 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st90;
	goto st0;
st101:
	if ( ++p == pe )
		goto _test_eof101;
case 101:
	if ( (*p) == 101 )
		goto st102;
	goto st0;
st102:
	if ( ++p == pe )
		goto _test_eof102;
case 102:
	if ( (*p) == 116 )
		goto st103;
	goto st0;
st103:
	if ( ++p == pe )
		goto _test_eof103;
case 103:
	switch( (*p) ) {
		case 32: goto st104;
		case 115: goto st107;
	}
	goto st0;
tr136:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
#line 75 "apps/memcached/ascii.rl"
	{ _keys.emplace_back(std::move(_key)); }
	goto st104;
st104:
	if ( ++p == pe )
		goto _test_eof104;
case 104:
#line 1446 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto st0;
	goto tr133;
tr133:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st105;
st105:
	if ( ++p == pe )
		goto _test_eof105;
case 105:
#line 1460 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr135;
		case 32: goto tr136;
	}
	goto st105;
tr135:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
#line 75 "apps/memcached/ascii.rl"
	{ _keys.emplace_back(std::move(_key)); }
	goto st106;
st106:
	if ( ++p == pe )
		goto _test_eof106;
case 106:
#line 1476 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 10: goto tr137;
		case 13: goto tr135;
		case 32: goto tr136;
	}
	goto st105;
tr137:
#line 75 "apps/memcached/ascii.rl"
	{ _state = state::cmd_get; }
	goto st198;
st198:
	if ( ++p == pe )
		goto _test_eof198;
case 198:
#line 1491 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr135;
		case 32: goto tr136;
	}
	goto st105;
st107:
	if ( ++p == pe )
		goto _test_eof107;
case 107:
	if ( (*p) == 32 )
		goto st108;
	goto st0;
tr142:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
#line 76 "apps/memcached/ascii.rl"
	{ _keys.emplace_back(std::move(_key)); }
	goto st108;
st108:
	if ( ++p == pe )
		goto _test_eof108;
case 108:
#line 1514 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto st0;
	goto tr139;
tr139:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st109;
st109:
	if ( ++p == pe )
		goto _test_eof109;
case 109:
#line 1528 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr141;
		case 32: goto tr142;
	}
	goto st109;
tr141:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
#line 76 "apps/memcached/ascii.rl"
	{ _keys.emplace_back(std::move(_key)); }
	goto st110;
st110:
	if ( ++p == pe )
		goto _test_eof110;
case 110:
#line 1544 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 10: goto tr143;
		case 13: goto tr141;
		case 32: goto tr142;
	}
	goto st109;
tr143:
#line 76 "apps/memcached/ascii.rl"
	{ _state = state::cmd_gets; }
	goto st199;
st199:
	if ( ++p == pe )
		goto _test_eof199;
case 199:
#line 1559 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr141;
		case 32: goto tr142;
	}
	goto st109;
st111:
	if ( ++p == pe )
		goto _test_eof111;
case 111:
	if ( (*p) == 110 )
		goto st112;
	goto st0;
st112:
	if ( ++p == pe )
		goto _test_eof112;
case 112:
	if ( (*p) == 99 )
		goto st113;
	goto st0;
st113:
	if ( ++p == pe )
		goto _test_eof113;
case 113:
	if ( (*p) == 114 )
		goto st114;
	goto st0;
st114:
	if ( ++p == pe )
		goto _test_eof114;
case 114:
	if ( (*p) == 32 )
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _test_eof115;
case 115:
	if ( (*p) == 32 )
		goto st0;
	goto tr148;
tr148:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st116;
st116:
	if ( ++p == pe )
		goto _test_eof116;
case 116:
#line 1610 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr150;
	goto st116;
tr150:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
	goto st117;
st117:
	if ( ++p == pe )
		goto _test_eof117;
case 117:
#line 1622 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr151;
	goto st0;
tr151:
#line 60 "apps/memcached/ascii.rl"
	{ _u64 = 0; }
#line 60 "apps/memcached/ascii.rl"
	{ _u64 *= 10; _u64 += (*p) - '0'; }
	goto st118;
tr154:
#line 60 "apps/memcached/ascii.rl"
	{ _u64 *= 10; _u64 += (*p) - '0'; }
	goto st118;
st118:
	if ( ++p == pe )
		goto _test_eof118;
case 118:
#line 1640 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr152;
		case 32: goto tr153;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr154;
	goto st0;
tr152:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st119;
st119:
	if ( ++p == pe )
		goto _test_eof119;
case 119:
#line 1656 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr155;
	goto st0;
tr153:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st120;
st120:
	if ( ++p == pe )
		goto _test_eof120;
case 120:
#line 1668 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st121;
	goto st0;
st121:
	if ( ++p == pe )
		goto _test_eof121;
case 121:
	if ( (*p) == 111 )
		goto st122;
	goto st0;
st122:
	if ( ++p == pe )
		goto _test_eof122;
case 122:
	if ( (*p) == 114 )
		goto st123;
	goto st0;
st123:
	if ( ++p == pe )
		goto _test_eof123;
case 123:
	if ( (*p) == 101 )
		goto st124;
	goto st0;
st124:
	if ( ++p == pe )
		goto _test_eof124;
case 124:
	if ( (*p) == 112 )
		goto st125;
	goto st0;
st125:
	if ( ++p == pe )
		goto _test_eof125;
case 125:
	if ( (*p) == 108 )
		goto st126;
	goto st0;
st126:
	if ( ++p == pe )
		goto _test_eof126;
case 126:
	if ( (*p) == 121 )
		goto tr162;
	goto st0;
tr162:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st127;
st127:
	if ( ++p == pe )
		goto _test_eof127;
case 127:
#line 1722 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st119;
	goto st0;
st128:
	if ( ++p == pe )
		goto _test_eof128;
case 128:
	if ( (*p) == 101 )
		goto st129;
	goto st0;
st129:
	if ( ++p == pe )
		goto _test_eof129;
case 129:
	if ( (*p) == 112 )
		goto st130;
	goto st0;
st130:
	if ( ++p == pe )
		goto _test_eof130;
case 130:
	if ( (*p) == 108 )
		goto st131;
	goto st0;
st131:
	if ( ++p == pe )
		goto _test_eof131;
case 131:
	if ( (*p) == 97 )
		goto st132;
	goto st0;
st132:
	if ( ++p == pe )
		goto _test_eof132;
case 132:
	if ( (*p) == 99 )
		goto st133;
	goto st0;
st133:
	if ( ++p == pe )
		goto _test_eof133;
case 133:
	if ( (*p) == 101 )
		goto st134;
	goto st0;
st134:
	if ( ++p == pe )
		goto _test_eof134;
case 134:
	if ( (*p) == 32 )
		goto st135;
	goto st0;
st135:
	if ( ++p == pe )
		goto _test_eof135;
case 135:
	if ( (*p) == 32 )
		goto st0;
	goto tr171;
tr171:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st136;
st136:
	if ( ++p == pe )
		goto _test_eof136;
case 136:
#line 1792 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr173;
	goto st136;
tr173:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
	goto st137;
st137:
	if ( ++p == pe )
		goto _test_eof137;
case 137:
#line 1804 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr174;
	goto st0;
tr174:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st138;
st138:
	if ( ++p == pe )
		goto _test_eof138;
case 138:
#line 1818 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr175;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st138;
	goto st0;
tr175:
#line 62 "apps/memcached/ascii.rl"
	{ _flags_str = str(); }
	goto st139;
st139:
	if ( ++p == pe )
		goto _test_eof139;
case 139:
#line 1832 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr177;
	goto st0;
tr177:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st140;
tr179:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st140;
st140:
	if ( ++p == pe )
		goto _test_eof140;
case 140:
#line 1850 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr178;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr179;
	goto st0;
tr178:
#line 63 "apps/memcached/ascii.rl"
	{ _expiration = _u32; }
	goto st141;
st141:
	if ( ++p == pe )
		goto _test_eof141;
case 141:
#line 1864 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr180;
	goto st0;
tr183:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st142;
tr180:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st142;
st142:
	if ( ++p == pe )
		goto _test_eof142;
case 142:
#line 1886 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr181;
		case 32: goto tr182;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr183;
	goto st0;
tr181:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st143;
st143:
	if ( ++p == pe )
		goto _test_eof143;
case 143:
#line 1904 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr184;
	goto st0;
tr184:
#line 70 "apps/memcached/ascii.rl"
	{ {
    prepush();
{ _fsm_stack[ _fsm_top++] = 144;goto st195;}} }
	goto st144;
st144:
	if ( ++p == pe )
		goto _test_eof144;
case 144:
#line 1918 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st145;
	goto st0;
st145:
	if ( ++p == pe )
		goto _test_eof145;
case 145:
	if ( (*p) == 10 )
		goto tr186;
	goto st0;
tr182:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st146;
st146:
	if ( ++p == pe )
		goto _test_eof146;
case 146:
#line 1939 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st147;
	goto st0;
st147:
	if ( ++p == pe )
		goto _test_eof147;
case 147:
	if ( (*p) == 111 )
		goto st148;
	goto st0;
st148:
	if ( ++p == pe )
		goto _test_eof148;
case 148:
	if ( (*p) == 114 )
		goto st149;
	goto st0;
st149:
	if ( ++p == pe )
		goto _test_eof149;
case 149:
	if ( (*p) == 101 )
		goto st150;
	goto st0;
st150:
	if ( ++p == pe )
		goto _test_eof150;
case 150:
	if ( (*p) == 112 )
		goto st151;
	goto st0;
st151:
	if ( ++p == pe )
		goto _test_eof151;
case 151:
	if ( (*p) == 108 )
		goto st152;
	goto st0;
st152:
	if ( ++p == pe )
		goto _test_eof152;
case 152:
	if ( (*p) == 121 )
		goto tr193;
	goto st0;
tr193:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st153;
st153:
	if ( ++p == pe )
		goto _test_eof153;
case 153:
#line 1993 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st143;
	goto st0;
st154:
	if ( ++p == pe )
		goto _test_eof154;
case 154:
	switch( (*p) ) {
		case 101: goto st155;
		case 116: goto st176;
	}
	goto st0;
st155:
	if ( ++p == pe )
		goto _test_eof155;
case 155:
	if ( (*p) == 116 )
		goto st156;
	goto st0;
st156:
	if ( ++p == pe )
		goto _test_eof156;
case 156:
	if ( (*p) == 32 )
		goto st157;
	goto st0;
st157:
	if ( ++p == pe )
		goto _test_eof157;
case 157:
	if ( (*p) == 32 )
		goto st0;
	goto tr199;
tr199:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st158;
st158:
	if ( ++p == pe )
		goto _test_eof158;
case 158:
#line 2037 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr201;
	goto st158;
tr201:
#line 61 "apps/memcached/ascii.rl"
	{ _key = memcache::item_key(str()); }
	goto st159;
st159:
	if ( ++p == pe )
		goto _test_eof159;
case 159:
#line 2049 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr202;
	goto st0;
tr202:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
	goto st160;
st160:
	if ( ++p == pe )
		goto _test_eof160;
case 160:
#line 2063 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr203;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st160;
	goto st0;
tr203:
#line 62 "apps/memcached/ascii.rl"
	{ _flags_str = str(); }
	goto st161;
st161:
	if ( ++p == pe )
		goto _test_eof161;
case 161:
#line 2077 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr205;
	goto st0;
tr205:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st162;
tr207:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st162;
st162:
	if ( ++p == pe )
		goto _test_eof162;
case 162:
#line 2095 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 32 )
		goto tr206;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr207;
	goto st0;
tr206:
#line 63 "apps/memcached/ascii.rl"
	{ _expiration = _u32; }
	goto st163;
st163:
	if ( ++p == pe )
		goto _test_eof163;
case 163:
#line 2109 "build/release/gen/apps/memcached/ascii.hh"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr208;
	goto st0;
tr211:
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st164;
tr208:
#line 36 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
}
#line 59 "apps/memcached/ascii.rl"
	{ _u32 = 0; }
#line 59 "apps/memcached/ascii.rl"
	{ _u32 *= 10; _u32 += (*p) - '0'; }
	goto st164;
st164:
	if ( ++p == pe )
		goto _test_eof164;
case 164:
#line 2131 "build/release/gen/apps/memcached/ascii.hh"
	switch( (*p) ) {
		case 13: goto tr209;
		case 32: goto tr210;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr211;
	goto st0;
tr209:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st165;
st165:
	if ( ++p == pe )
		goto _test_eof165;
case 165:
#line 2149 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 10 )
		goto tr212;
	goto st0;
tr212:
#line 70 "apps/memcached/ascii.rl"
	{ {
    prepush();
{ _fsm_stack[ _fsm_top++] = 166;goto st195;}} }
	goto st166;
st166:
	if ( ++p == pe )
		goto _test_eof166;
case 166:
#line 2163 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st167;
	goto st0;
st167:
	if ( ++p == pe )
		goto _test_eof167;
case 167:
	if ( (*p) == 10 )
		goto tr214;
	goto st0;
tr210:
#line 64 "apps/memcached/ascii.rl"
	{ _size = _u32; _size_str = str(); }
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = false; }
	goto st168;
st168:
	if ( ++p == pe )
		goto _test_eof168;
case 168:
#line 2184 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 110 )
		goto st169;
	goto st0;
st169:
	if ( ++p == pe )
		goto _test_eof169;
case 169:
	if ( (*p) == 111 )
		goto st170;
	goto st0;
st170:
	if ( ++p == pe )
		goto _test_eof170;
case 170:
	if ( (*p) == 114 )
		goto st171;
	goto st0;
st171:
	if ( ++p == pe )
		goto _test_eof171;
case 171:
	if ( (*p) == 101 )
		goto st172;
	goto st0;
st172:
	if ( ++p == pe )
		goto _test_eof172;
case 172:
	if ( (*p) == 112 )
		goto st173;
	goto st0;
st173:
	if ( ++p == pe )
		goto _test_eof173;
case 173:
	if ( (*p) == 108 )
		goto st174;
	goto st0;
st174:
	if ( ++p == pe )
		goto _test_eof174;
case 174:
	if ( (*p) == 121 )
		goto tr221;
	goto st0;
tr221:
#line 66 "apps/memcached/ascii.rl"
	{ _noreply = true; }
	goto st175;
st175:
	if ( ++p == pe )
		goto _test_eof175;
case 175:
#line 2238 "build/release/gen/apps/memcached/ascii.hh"
	if ( (*p) == 13 )
		goto st165;
	goto st0;
st176:
	if ( ++p == pe )
		goto _test_eof176;
case 176:
	if ( (*p) == 97 )
		goto st177;
	goto st0;
st177:
	if ( ++p == pe )
		goto _test_eof177;
case 177:
	if ( (*p) == 116 )
		goto st178;
	goto st0;
st178:
	if ( ++p == pe )
		goto _test_eof178;
case 178:
	if ( (*p) == 115 )
		goto st179;
	goto st0;
st179:
	if ( ++p == pe )
		goto _test_eof179;
case 179:
	switch( (*p) ) {
		case 13: goto st180;
		case 32: goto st181;
	}
	goto st0;
st180:
	if ( ++p == pe )
		goto _test_eof180;
case 180:
	if ( (*p) == 10 )
		goto tr228;
	goto st0;
st181:
	if ( ++p == pe )
		goto _test_eof181;
case 181:
	if ( (*p) == 104 )
		goto st182;
	goto st0;
st182:
	if ( ++p == pe )
		goto _test_eof182;
case 182:
	if ( (*p) == 97 )
		goto st183;
	goto st0;
st183:
	if ( ++p == pe )
		goto _test_eof183;
case 183:
	if ( (*p) == 115 )
		goto st184;
	goto st0;
st184:
	if ( ++p == pe )
		goto _test_eof184;
case 184:
	if ( (*p) == 104 )
		goto st185;
	goto st0;
st185:
	if ( ++p == pe )
		goto _test_eof185;
case 185:
	if ( (*p) == 13 )
		goto st186;
	goto st0;
st186:
	if ( ++p == pe )
		goto _test_eof186;
case 186:
	if ( (*p) == 10 )
		goto tr234;
	goto st0;
st187:
	if ( ++p == pe )
		goto _test_eof187;
case 187:
	if ( (*p) == 101 )
		goto st188;
	goto st0;
st188:
	if ( ++p == pe )
		goto _test_eof188;
case 188:
	if ( (*p) == 114 )
		goto st189;
	goto st0;
st189:
	if ( ++p == pe )
		goto _test_eof189;
case 189:
	if ( (*p) == 115 )
		goto st190;
	goto st0;
st190:
	if ( ++p == pe )
		goto _test_eof190;
case 190:
	if ( (*p) == 105 )
		goto st191;
	goto st0;
st191:
	if ( ++p == pe )
		goto _test_eof191;
case 191:
	if ( (*p) == 111 )
		goto st192;
	goto st0;
st192:
	if ( ++p == pe )
		goto _test_eof192;
case 192:
	if ( (*p) == 110 )
		goto st193;
	goto st0;
st193:
	if ( ++p == pe )
		goto _test_eof193;
case 193:
	if ( (*p) == 13 )
		goto st194;
	goto st0;
st194:
	if ( ++p == pe )
		goto _test_eof194;
case 194:
	if ( (*p) == 10 )
		goto tr242;
	goto st0;
st195:
	if ( ++p == pe )
		goto _test_eof195;
case 195:
	goto tr243;
tr243:
#line 40 "apps/memcached/ascii.rl"
	{
    g.mark_start(p);
    _size_left = _size;
}
#line 45 "apps/memcached/ascii.rl"
	{
    auto len = std::min((uint32_t)(pe - p), _size_left);
    _size_left -= len;
    p += len;
    if (_size_left == 0) {
        _blob = str();
        p--;
        { _fsm_cs =  _fsm_stack[-- _fsm_top];{
    postpop();
}goto _again;}
    }
    p--;
}
	goto st200;
tr244:
#line 45 "apps/memcached/ascii.rl"
	{
    auto len = std::min((uint32_t)(pe - p), _size_left);
    _size_left -= len;
    p += len;
    if (_size_left == 0) {
        _blob = str();
        p--;
        { _fsm_cs =  _fsm_stack[-- _fsm_top];{
    postpop();
}goto _again;}
    }
    p--;
}
	goto st200;
st200:
	if ( ++p == pe )
		goto _test_eof200;
case 200:
#line 2423 "build/release/gen/apps/memcached/ascii.hh"
	goto tr244;
	}
	_test_eof1:  _fsm_cs = 1; goto _test_eof; 
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
	_test_eof196:  _fsm_cs = 196; goto _test_eof; 
	_test_eof16:  _fsm_cs = 16; goto _test_eof; 
	_test_eof17:  _fsm_cs = 17; goto _test_eof; 
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
	_test_eof34:  _fsm_cs = 34; goto _test_eof; 
	_test_eof35:  _fsm_cs = 35; goto _test_eof; 
	_test_eof36:  _fsm_cs = 36; goto _test_eof; 
	_test_eof37:  _fsm_cs = 37; goto _test_eof; 
	_test_eof38:  _fsm_cs = 38; goto _test_eof; 
	_test_eof39:  _fsm_cs = 39; goto _test_eof; 
	_test_eof40:  _fsm_cs = 40; goto _test_eof; 
	_test_eof41:  _fsm_cs = 41; goto _test_eof; 
	_test_eof42:  _fsm_cs = 42; goto _test_eof; 
	_test_eof43:  _fsm_cs = 43; goto _test_eof; 
	_test_eof44:  _fsm_cs = 44; goto _test_eof; 
	_test_eof45:  _fsm_cs = 45; goto _test_eof; 
	_test_eof46:  _fsm_cs = 46; goto _test_eof; 
	_test_eof47:  _fsm_cs = 47; goto _test_eof; 
	_test_eof48:  _fsm_cs = 48; goto _test_eof; 
	_test_eof49:  _fsm_cs = 49; goto _test_eof; 
	_test_eof50:  _fsm_cs = 50; goto _test_eof; 
	_test_eof51:  _fsm_cs = 51; goto _test_eof; 
	_test_eof52:  _fsm_cs = 52; goto _test_eof; 
	_test_eof53:  _fsm_cs = 53; goto _test_eof; 
	_test_eof54:  _fsm_cs = 54; goto _test_eof; 
	_test_eof55:  _fsm_cs = 55; goto _test_eof; 
	_test_eof56:  _fsm_cs = 56; goto _test_eof; 
	_test_eof57:  _fsm_cs = 57; goto _test_eof; 
	_test_eof58:  _fsm_cs = 58; goto _test_eof; 
	_test_eof59:  _fsm_cs = 59; goto _test_eof; 
	_test_eof60:  _fsm_cs = 60; goto _test_eof; 
	_test_eof61:  _fsm_cs = 61; goto _test_eof; 
	_test_eof62:  _fsm_cs = 62; goto _test_eof; 
	_test_eof63:  _fsm_cs = 63; goto _test_eof; 
	_test_eof64:  _fsm_cs = 64; goto _test_eof; 
	_test_eof65:  _fsm_cs = 65; goto _test_eof; 
	_test_eof66:  _fsm_cs = 66; goto _test_eof; 
	_test_eof67:  _fsm_cs = 67; goto _test_eof; 
	_test_eof68:  _fsm_cs = 68; goto _test_eof; 
	_test_eof69:  _fsm_cs = 69; goto _test_eof; 
	_test_eof70:  _fsm_cs = 70; goto _test_eof; 
	_test_eof71:  _fsm_cs = 71; goto _test_eof; 
	_test_eof197:  _fsm_cs = 197; goto _test_eof; 
	_test_eof72:  _fsm_cs = 72; goto _test_eof; 
	_test_eof73:  _fsm_cs = 73; goto _test_eof; 
	_test_eof74:  _fsm_cs = 74; goto _test_eof; 
	_test_eof75:  _fsm_cs = 75; goto _test_eof; 
	_test_eof76:  _fsm_cs = 76; goto _test_eof; 
	_test_eof77:  _fsm_cs = 77; goto _test_eof; 
	_test_eof78:  _fsm_cs = 78; goto _test_eof; 
	_test_eof79:  _fsm_cs = 79; goto _test_eof; 
	_test_eof80:  _fsm_cs = 80; goto _test_eof; 
	_test_eof81:  _fsm_cs = 81; goto _test_eof; 
	_test_eof82:  _fsm_cs = 82; goto _test_eof; 
	_test_eof83:  _fsm_cs = 83; goto _test_eof; 
	_test_eof84:  _fsm_cs = 84; goto _test_eof; 
	_test_eof85:  _fsm_cs = 85; goto _test_eof; 
	_test_eof86:  _fsm_cs = 86; goto _test_eof; 
	_test_eof87:  _fsm_cs = 87; goto _test_eof; 
	_test_eof88:  _fsm_cs = 88; goto _test_eof; 
	_test_eof89:  _fsm_cs = 89; goto _test_eof; 
	_test_eof90:  _fsm_cs = 90; goto _test_eof; 
	_test_eof91:  _fsm_cs = 91; goto _test_eof; 
	_test_eof92:  _fsm_cs = 92; goto _test_eof; 
	_test_eof93:  _fsm_cs = 93; goto _test_eof; 
	_test_eof94:  _fsm_cs = 94; goto _test_eof; 
	_test_eof95:  _fsm_cs = 95; goto _test_eof; 
	_test_eof96:  _fsm_cs = 96; goto _test_eof; 
	_test_eof97:  _fsm_cs = 97; goto _test_eof; 
	_test_eof98:  _fsm_cs = 98; goto _test_eof; 
	_test_eof99:  _fsm_cs = 99; goto _test_eof; 
	_test_eof100:  _fsm_cs = 100; goto _test_eof; 
	_test_eof101:  _fsm_cs = 101; goto _test_eof; 
	_test_eof102:  _fsm_cs = 102; goto _test_eof; 
	_test_eof103:  _fsm_cs = 103; goto _test_eof; 
	_test_eof104:  _fsm_cs = 104; goto _test_eof; 
	_test_eof105:  _fsm_cs = 105; goto _test_eof; 
	_test_eof106:  _fsm_cs = 106; goto _test_eof; 
	_test_eof198:  _fsm_cs = 198; goto _test_eof; 
	_test_eof107:  _fsm_cs = 107; goto _test_eof; 
	_test_eof108:  _fsm_cs = 108; goto _test_eof; 
	_test_eof109:  _fsm_cs = 109; goto _test_eof; 
	_test_eof110:  _fsm_cs = 110; goto _test_eof; 
	_test_eof199:  _fsm_cs = 199; goto _test_eof; 
	_test_eof111:  _fsm_cs = 111; goto _test_eof; 
	_test_eof112:  _fsm_cs = 112; goto _test_eof; 
	_test_eof113:  _fsm_cs = 113; goto _test_eof; 
	_test_eof114:  _fsm_cs = 114; goto _test_eof; 
	_test_eof115:  _fsm_cs = 115; goto _test_eof; 
	_test_eof116:  _fsm_cs = 116; goto _test_eof; 
	_test_eof117:  _fsm_cs = 117; goto _test_eof; 
	_test_eof118:  _fsm_cs = 118; goto _test_eof; 
	_test_eof119:  _fsm_cs = 119; goto _test_eof; 
	_test_eof120:  _fsm_cs = 120; goto _test_eof; 
	_test_eof121:  _fsm_cs = 121; goto _test_eof; 
	_test_eof122:  _fsm_cs = 122; goto _test_eof; 
	_test_eof123:  _fsm_cs = 123; goto _test_eof; 
	_test_eof124:  _fsm_cs = 124; goto _test_eof; 
	_test_eof125:  _fsm_cs = 125; goto _test_eof; 
	_test_eof126:  _fsm_cs = 126; goto _test_eof; 
	_test_eof127:  _fsm_cs = 127; goto _test_eof; 
	_test_eof128:  _fsm_cs = 128; goto _test_eof; 
	_test_eof129:  _fsm_cs = 129; goto _test_eof; 
	_test_eof130:  _fsm_cs = 130; goto _test_eof; 
	_test_eof131:  _fsm_cs = 131; goto _test_eof; 
	_test_eof132:  _fsm_cs = 132; goto _test_eof; 
	_test_eof133:  _fsm_cs = 133; goto _test_eof; 
	_test_eof134:  _fsm_cs = 134; goto _test_eof; 
	_test_eof135:  _fsm_cs = 135; goto _test_eof; 
	_test_eof136:  _fsm_cs = 136; goto _test_eof; 
	_test_eof137:  _fsm_cs = 137; goto _test_eof; 
	_test_eof138:  _fsm_cs = 138; goto _test_eof; 
	_test_eof139:  _fsm_cs = 139; goto _test_eof; 
	_test_eof140:  _fsm_cs = 140; goto _test_eof; 
	_test_eof141:  _fsm_cs = 141; goto _test_eof; 
	_test_eof142:  _fsm_cs = 142; goto _test_eof; 
	_test_eof143:  _fsm_cs = 143; goto _test_eof; 
	_test_eof144:  _fsm_cs = 144; goto _test_eof; 
	_test_eof145:  _fsm_cs = 145; goto _test_eof; 
	_test_eof146:  _fsm_cs = 146; goto _test_eof; 
	_test_eof147:  _fsm_cs = 147; goto _test_eof; 
	_test_eof148:  _fsm_cs = 148; goto _test_eof; 
	_test_eof149:  _fsm_cs = 149; goto _test_eof; 
	_test_eof150:  _fsm_cs = 150; goto _test_eof; 
	_test_eof151:  _fsm_cs = 151; goto _test_eof; 
	_test_eof152:  _fsm_cs = 152; goto _test_eof; 
	_test_eof153:  _fsm_cs = 153; goto _test_eof; 
	_test_eof154:  _fsm_cs = 154; goto _test_eof; 
	_test_eof155:  _fsm_cs = 155; goto _test_eof; 
	_test_eof156:  _fsm_cs = 156; goto _test_eof; 
	_test_eof157:  _fsm_cs = 157; goto _test_eof; 
	_test_eof158:  _fsm_cs = 158; goto _test_eof; 
	_test_eof159:  _fsm_cs = 159; goto _test_eof; 
	_test_eof160:  _fsm_cs = 160; goto _test_eof; 
	_test_eof161:  _fsm_cs = 161; goto _test_eof; 
	_test_eof162:  _fsm_cs = 162; goto _test_eof; 
	_test_eof163:  _fsm_cs = 163; goto _test_eof; 
	_test_eof164:  _fsm_cs = 164; goto _test_eof; 
	_test_eof165:  _fsm_cs = 165; goto _test_eof; 
	_test_eof166:  _fsm_cs = 166; goto _test_eof; 
	_test_eof167:  _fsm_cs = 167; goto _test_eof; 
	_test_eof168:  _fsm_cs = 168; goto _test_eof; 
	_test_eof169:  _fsm_cs = 169; goto _test_eof; 
	_test_eof170:  _fsm_cs = 170; goto _test_eof; 
	_test_eof171:  _fsm_cs = 171; goto _test_eof; 
	_test_eof172:  _fsm_cs = 172; goto _test_eof; 
	_test_eof173:  _fsm_cs = 173; goto _test_eof; 
	_test_eof174:  _fsm_cs = 174; goto _test_eof; 
	_test_eof175:  _fsm_cs = 175; goto _test_eof; 
	_test_eof176:  _fsm_cs = 176; goto _test_eof; 
	_test_eof177:  _fsm_cs = 177; goto _test_eof; 
	_test_eof178:  _fsm_cs = 178; goto _test_eof; 
	_test_eof179:  _fsm_cs = 179; goto _test_eof; 
	_test_eof180:  _fsm_cs = 180; goto _test_eof; 
	_test_eof181:  _fsm_cs = 181; goto _test_eof; 
	_test_eof182:  _fsm_cs = 182; goto _test_eof; 
	_test_eof183:  _fsm_cs = 183; goto _test_eof; 
	_test_eof184:  _fsm_cs = 184; goto _test_eof; 
	_test_eof185:  _fsm_cs = 185; goto _test_eof; 
	_test_eof186:  _fsm_cs = 186; goto _test_eof; 
	_test_eof187:  _fsm_cs = 187; goto _test_eof; 
	_test_eof188:  _fsm_cs = 188; goto _test_eof; 
	_test_eof189:  _fsm_cs = 189; goto _test_eof; 
	_test_eof190:  _fsm_cs = 190; goto _test_eof; 
	_test_eof191:  _fsm_cs = 191; goto _test_eof; 
	_test_eof192:  _fsm_cs = 192; goto _test_eof; 
	_test_eof193:  _fsm_cs = 193; goto _test_eof; 
	_test_eof194:  _fsm_cs = 194; goto _test_eof; 
	_test_eof195:  _fsm_cs = 195; goto _test_eof; 
	_test_eof200:  _fsm_cs = 200; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch (  _fsm_cs ) {
	case 1: 
#line 85 "apps/memcached/ascii.rl"
	{ _state = state::eof; }
	break;
#line 2635 "build/release/gen/apps/memcached/ascii.hh"
	}
	}

	_out: {}
	}

#line 142 "apps/memcached/ascii.rl"
        if (_state != state::error) {
            return p;
        }
        if (p != pe) {
            p = pe;
            return p;
        }
        return nullptr;
    }
    bool eof() const {
        return _state == state::eof;
    }
};
