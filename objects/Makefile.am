AUTUMAKE_OPTIONS = foreign

INCLUDES = \
-I$(top_srcdir)/include \
-I$(top_srcdir)/../pjlib/include \
-I$(top_srcdir)/../pjlib/include/pj \
-I$(top_srcdir)/../pjlib-util/include

libpjmsrp_a_CFLAGS = -D_EVENTDES -D_GNU_SOURCE -DHAS_SET_STACK -DWEBRTC_POSIX -DWEBRTC_THREAD_RR \
-DWEBRTC_LINUX -DFEATURE_ENABLE_SSL -DHAVE_OPENSSL_SSL_H -DSSL_USE_OPENSSL -DIA64 -O2


noinst_LIBRARIES = libpjmsrp.a
#########################################################

libpjmsrp_a_SOURCES= \
$(top_srcdir)/source/pjmsrp_parser_header_byte_range.c \
$(top_srcdir)/source/pjmsrp_parser_header_max_expires.c \
$(top_srcdir)/source/pjmsrp_parser_header_use_path.c \
$(top_srcdir)/source/pjmsrp_parser_header_content_type.c \
$(top_srcdir)/source/pjmsrp_parser_header_message_id.c \
$(top_srcdir)/source/pjmsrp_parser_header_www_authenticate.c \
$(top_srcdir)/source/pjmsrp_common.c \
$(top_srcdir)/source/pjmsrp_parser_header_dummy.c \
$(top_srcdir)/source/pjmsrp_parser_header_min_expires.c \
$(top_srcdir)/source/pjmsrp_parser_message.c \
$(top_srcdir)/source/pjmsrp_header.c \
$(top_srcdir)/source/pjmsrp_parser_header_expires.c \
$(top_srcdir)/source/pjmsrp_parser_header_status.c \
$(top_srcdir)/source/pjmsrp_parser_uri.c \
$(top_srcdir)/source/pjmsrp_message.c \
$(top_srcdir)/source/pjmsrp_parser_header_failure_report.c \
$(top_srcdir)/source/pjmsrp_parser_header_success_report.c \
$(top_srcdir)/source/pjmsrp_ragel_state.c \
$(top_srcdir)/source/pjmsrp_parser_header_authorization.c \
$(top_srcdir)/source/pjmsrp_parser_header_from_path.c \
$(top_srcdir)/source/pjmsrp_parser_header_to_path.c \
$(top_srcdir)/source/pjmsrp_uri.c \
$(top_srcdir)/source/pjmsrp.c

#########################################################
