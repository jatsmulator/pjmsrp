/*
* Copyright (C) 2016 John Li.
*
* Contact: John Li <jatsmulator(at)gmail.com>
*
* PJRCS is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* PJRCS is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with PJRCS; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "pjmsrp.h"

#define MSRP_MSG_REQUEST \
	"MSRP a786hjs2 SEND\r\n" \
	"To-Path: msrp://biloxi.example.com:12763/kjhd37s2s20w2a;tcp\r\n" \
	"From-Path: msrp://atlanta.example.com:7654/jshA7weztas;tcp\r\n" \
	"Message-ID: 87652491\r\n" \
	"Byte-Dummy: 1-25/25\r\n" \
	"Byte-Range: 1-23/23\r\n" \
	"Failure-Report: partial\r\n" \
    "Success-Report: yes\r\n" \
	"Content-Type: text/plain;charset=utf8\r\n" \
	"\r\n" \
	"ab\r\nc\r\n" \
	"-------a786hjs2$\r\n"

#define MSRP_MSG_REQUEST2 \
	"MSRP 146969566132900000Z SEND\r\n"\
	"To-Path: msrp://211.138.118.206:53542/2aaf0dcd2694;tcp\r\n"\
	"From-Path: msrp://192.168.104.76:40000/1470087498348;tcp\r\n"\
	"Message-ID: 146969566132900000\r\n"\
	"Byte-Range: 1-6924/6924\r\n"\
	"Success-Report: no\r\n"\
	"Content-Type: message/cpim\r\n"\
	"\r\n"\
	"From: <sip:+8618421112019@ims.mnc000.mcc460.3gppnetwork.org>\r\n"\
	"To: <tel:+8618421112020>\r\n"\
	"NS: imdn<urn:ietf:params:imdn>\r\n"\
	"imdn.Message-ID: 146969566132900000\r\n"\
	"DateTime: 2016-07-28T16:47:41Z\r\n"\
	"imdn.Disposition-Notification: positive-delivery, negative-delivery, display\r\n"\
	"\r\n"\
	"Content-Type: text/plain;charset=UTF-8\r\n"\
	"Content-Length: 6556\r\n"\
	"Content-Transfer-Encoding: base64\r\n"\
	"\r\n"\
	"MTIzNDU2Nzg5MDExMTExMTExMXRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMT"\
	"YwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0K"\
	"dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI"\
	"3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdD"\
	"IwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzd"\
	"HRlc3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYw"\
	"NDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGV"\
	"zdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dG"\
	"VzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwM"\
	"TYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRl"\
	"c3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI"\
	"3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdD"\
	"IwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzd"\
	"HRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYw"\
	"NDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3Q"\
	"yMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dG"\
	"VzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwM"\
	"TYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRl"\
	"c3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI"\
	"3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMD"\
	"E2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzd"\
	"HRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYw"\
	"NDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3Q"\
	"yMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dG"\
	"VzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2M"\
	"DQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRl"\
	"c3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI"\
	"3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMD"\
	"E2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzd"\
	"HRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQy"\
	"N3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3Q"\
	"yMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dG"\
	"VzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2M"\
	"DQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRl"\
	"c3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3R"\
	"lc3QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMD"\
	"E2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzd"\
	"HRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQy"\
	"N3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3Q"\
	"yMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3"\
	"QNCnRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2M"\
	"DQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRl"\
	"c3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3R"\
	"lc3R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMD"\
	"E2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNC"\
	"nRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQy"\
	"N3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3Q"\
	"yMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3"\
	"R0ZXN0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2M"\
	"DQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRl"\
	"c3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3R"\
	"lc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE"\
	"2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZX"\
	"N0MjAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN"\
	"3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRlc3Qy"\
	"MDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R"\
	"0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MD"\
	"QyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0M"\
	"jAxNjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rl"\
	"c3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE"\
	"2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZX"\
	"N0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN"\
	"3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAx"\
	"NjA0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R"\
	"0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MD"\
	"QyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0M"\
	"jAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rl"\
	"c3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA"\
	"0Mjd0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZX"\
	"N0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN"\
	"3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAx"\
	"NjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R"\
	"0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mj"\
	"d0ZXN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0M"\
	"jAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rl"\
	"c3R0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA"\
	"0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZX"\
	"N0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0Z"\
	"XN0DQp0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAx"\
	"NjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3QNCnRlc3QyMDE2MDQyN3Rlc3R"\
	"0ZXN0MjAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mj"\
	"d0ZXN0dGVzdDIwMTYwNDI3dGVzdA0KdGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0M"\
	"jAxNjA0Mjd0ZXN0dGVzdDIwMTYwNDI3dGVzdHRlc3QyMDE2MDQyN3Rlc3R0ZXN0MjAxNjA0Mjd0ZXN0\r\n"\
	"-------146969566132900000Z$\r\n"


#define MSRP_MSG_RESPONSE \
	"MSRP a786hjs2 200 OK\r\n" \
	"To-Path: msrp://atlanta.example.com:7654/jshA7weztas;tcp\r\n" \
	"From-Path: msrp://biloxi.example.com:12763/kjhd37s2s20w2a;tcp\r\n" \
	"-------a786hjs2$\r\nMSRP 000"

#define MSRP_MSG_REPORT \
	"MSRP dkei38sd REPORT\r\n" \
	"To-Path: msrp://alicepc.example.com:7777/iau39soe2843z;tcp\r\n" \
	"From-Path: msrp://bob.example.com:8888/9di4eae923wzd;tcp\r\n" \
	"Message-ID: 12339sdqwer\r\n" \
	"Byte-Range: 1-106/106\r\n" \
	"Status: 000 200 OK\r\n" \
	"-------dkei38sd$\r\nMSRP 000"

#define MSRP_MSG_TO_TEST MSRP_MSG_REQUEST2

int main()
{
	pj_caching_pool cp;
	pj_pool_t* pool;
	pj_status_t status;

    pjmsrp_message_t *message;
    pjmsrp_request_t* requestMessage;
    //const pjmsrp_header_dummy_t* header;
    pj_size_t msg_size;

    pj_str_t buffer = {NULL, 0};

	const char* uris[] =
	{
		"From-Path: msrp://atlanta.example.com:7654/jshA7weztas;tcp;p1=1;p2=2",
		"To-Path: msrps://atlanta.example.com:7654/jshA7weztas;tcp",
		"Message-ID: 1469695661674",
		"Byte-Range: 1-6924/6924",
		"Success-Report: no",
		"Failure-Report: yes",
		"Content-Type: text/plain;charset=UTF-8",
		// hostname, IPv4 and IPv6 (without userinfo and with port)
		"msrp://biloxi.msrp.com:12763/kjhd37s2s20w2a;sctp",
		"msrps://192.168.0.10:7654/jshA7weztas;tcp;p3=4",
		"msrps://[::127]:7654/jshA7weztas;tcp;p=0",

		// hostname, IPv4 and IPv6 (without userinfo and without port)
		"msrp://biloxi.msrp.com/kjhd37s2s20w2a;sctp",
		"msrps://192.168.0.10/jshA7weztas;tcp;p3=4",
		"msrps://[::127]/jshA7weztas;tcp;p=0",

		// hostname, IPv4 and IPv6 (with userinfo and with port)
		"msrp://bob@biloxi.msrp.com:12763/kjhd37s2s20w2a;sctp",
		"msrps://alice@192.168.0.10:7654/jshA7weztas;tcp;p3=4",
		"msrps://carol@[::127]:7654/jshA7weztas;tcp;p=0",

		// hostname, IPv4 and IPv6 (with userinfo and without port)
		"msrp://bob@biloxi.msrp.com/kjhd37s2s20w2a;sctp",
		"msrps://alice@192.168.0.10/jshA7weztas;tcp;p3=4",
		"msrps://carol@[::127]/jshA7weztas;tcp;p=0",

		// without session_id
		"msrps://[::127]:7654;tcp;p=0",
	};

	pjmsrp_uri_t* uri;
	pjmsrp_header_from_path_t* fromPathURI;
	pjmsrp_header_to_path_t* toPathURI;
	pjmsrp_header_message_id_t* messageID;
	pjmsrp_header_byte_range_t* byteRange;
	pjmsrp_header_success_report_t* successReport;
	pjmsrp_header_failure_report_t* failureReport;
	pjmsrp_header_content_type_t* contentType;
	// Must init PJLIB before anything else
	status = pj_init();
	if (status != PJ_SUCCESS) {
		return 1;
	}
	pj_log_set_level(6);
	pj_caching_pool_init(&cp, NULL, 1024*1024 );

	pool = pj_pool_create(&cp.factory, // the factory
	"pool1", // pool's name
	4000, // initial size
	4000, // increment size
	NULL
	); // use default callback.

	if((requestMessage = pjmsrp_message_parse(pool, MSRP_MSG_TO_TEST, strlen(MSRP_MSG_TO_TEST)))) {
		PJ_LOG(2, (__FILE__, "slen:%d, ptr:%s",
			requestMessage->Content.slen, requestMessage->Content.ptr));
	}

    if((message = pjmsrp_message_parse(pool, MSRP_MSG_REQUEST, strlen(MSRP_MSG_REQUEST)))) {
    	pjmsrp_response_t* response = pjmsrp_create_response(pool, message, 202, "Accepted");
    	PJ_LOG(2, (__FILE__, "Status Code:%d, Reason:%s",
    			response->line.response.status, response->line.response.comment.ptr));
    }


	requestMessage =  pjmsrp_create_bodiless(pool, NULL, NULL);

	fromPathURI = pjmsrp_header_from_path_parse(pool,  uris[0], strlen(uris[0]));
	PJ_LOG(2, (__FILE__, "From-Path: %s", fromPathURI->uri->authority.host.ptr));

	buffer.ptr = NULL; buffer.slen = 0;
	pjmsrp_header_from_path_tostring(fromPathURI, &buffer);
	PJ_LOG(2, (__FILE__, "From-Path: %s", buffer.ptr));

	toPathURI 	= pjmsrp_header_to_path_parse(pool,  uris[1], strlen(uris[1]));
	PJ_LOG(2, (__FILE__, "To-Path: %s", toPathURI->uri->authority.host.ptr));
	buffer.ptr = NULL; buffer.slen = 0;
	pjmsrp_header_to_path_tostring(toPathURI, &buffer);
	PJ_LOG(2, (__FILE__, "To-Path: %s", buffer.ptr));

	messageID 	= pjmsrp_header_message_id_parse(pool,  uris[2], strlen(uris[2]));
	PJ_LOG(2, (__FILE__, "Message-ID: %s", messageID->value.ptr));
	buffer.ptr = NULL; buffer.slen = 0;
	pjmsrp_header_message_id_tostring(messageID, &buffer);
	PJ_LOG(2, (__FILE__, "Message-ID: %s", buffer.ptr));

	buffer.ptr = NULL; buffer.slen = 0;
	byteRange	= pjmsrp_header_byte_range_parse(pool,  uris[3], strlen(uris[3]));
	PJ_LOG(2, (__FILE__, "Byte-Range: %d-%d/%d", byteRange->start, byteRange->end, byteRange->total));

	buffer.ptr = NULL; buffer.slen = 0;
	pjmsrp_header_byte_range_tostring(byteRange, &buffer);
	PJ_LOG(2, (__FILE__, "Byte-Range: %s", buffer.ptr));

	byteRange = pjmsrp_header_byte_range_create(pool, 1, 6024, 6024);
	buffer.ptr = NULL; buffer.slen = 0;
	pjmsrp_header_byte_range_tostring(byteRange, &buffer);
	PJ_LOG(2, (__FILE__, "Byte-Range: %s", buffer.ptr));

	contentType = pjmsrp_header_content_type_parse(pool,  uris[6], strlen(uris[6]));
	buffer.ptr = NULL; buffer.slen = 0;
	pjmsrp_header_content_type_tostring(contentType, &buffer);
	PJ_LOG(2, (__FILE__, "Content-Type: %s", buffer.ptr));

	successReport = pjmsrp_header_success_report_parse(pool,  uris[4], strlen(uris[4]));
	PJ_LOG(2, (__FILE__, "Success-Report: %s", (successReport->yes == 1)?"yes":"no" ));

	failureReport = pjmsrp_header_failure_report_parse(pool,  uris[5], strlen(uris[5]));
	PJ_LOG(2, (__FILE__, "Failure-Report: %s", (failureReport->type == freport_yes)?"yes":(failureReport->type == freport_no)? "no": "partial"));


	pj_pool_release(pool);
	pj_caching_pool_destroy(&cp);
	return 0;
}
