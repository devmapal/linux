#undef TRACE_SYSTEM
#define TRACE_SYSTEM ozwpan

#if !defined(_OZWPAN_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _OZWPAN_TRACE_H

#include <linux/tracepoint.h>


TRACE_EVENT(ozwpan_cdev_dealloc_ctx,

	TP_PROTO(struct oz_serial_ctx *ctx),

	TP_ARGS(ctx),

	TP_STRUCT__entry(
		__field(	u8,	tx_seq_num	)
		__field(	u8,	rx_seq_num	)
		__field(	u8,	rd_in		)
		__field(	u8,	rd_out		)
	),

	TP_fast_assign(
		__entry->tx_seq_num = ctx->tx_seq_num;
		__entry->rx_seq_num = ctx->rx_seq_num;
		__entry->rd_in = ctx->rd_in;
		__entry->rd_out = ctx->rd_out;
	),

	TP_printk("tx_seq_num 0x%x rx_seq_num 0x%x rd_in 0x%x rd_out 0x%x",
		__entry->tx_seq_num, __entry->rx_seq_num, __entry->rd_in,
		__entry->rd_out)
);

TRACE_EVENT(ozwpan_cdev_open,

	TP_PROTO(struct inode *inode),

	TP_ARGS(inode),

	TP_STRUCT__entry(
		__field(	unsigned,	major	)
		__field(	unsigned,	minor	)
	),

	TP_fast_assign(
		__entry->major = imajor(inode);
		__entry->minor = iminor(inode);
	),

	TP_printk("major %d minor %d", __entry->major, __entry->minor);
);

TRACE_EVENT_CLASS(ozwpan_cdev_ioctl_class,

	TP_PROTO(unsigned int cmd, unsigned long arg),

	TP_ARGS(cmd, arg),

	TP_STRUCT__entry(
		__field(	unsigned int,	cmd	)
		__field(	unsigned long,	arg	)
	),

	TP_fast_assign(
		__entry->cmd = cmd;
		__entry->arg = arg;
	),

	TP_printk("cmd %s arg %lu", __print_symbolic(__entry->cmd, \
		{ OZ_IOCTL_GET_PD_LIST,		"OZ_IOCTL_GET_PD_LIST" }, \
		{ OZ_IOCTL_SET_ACTIVE_PD,	"OZ_IOCTL_SET_ACTIVE_PD" }, \
		{ OZ_IOCTL_GET_ACTIVE_PD,	"OZ_IOCTL_GET_ACTIVE_PD" }),
		arg)
);

#define DEFINE_CDEV_IOCTL_EVENT(name) \
DEFINE_EVENT(ozwpan_cdev_ioctl_class, name, \
	TP_PROTO(unsigned int cmd, unsigned long arg), \
	TP_ARGS(cmd, arg))
DEFINE_CDEV_IOCTL_EVENT(ozwpan_cdev_ioctl_get_pd_list);
DEFINE_CDEV_IOCTL_EVENT(ozwpan_cdev_ioctl_set_active_pd);
DEFINE_CDEV_IOCTL_EVENT(ozwpan_cdev_ioctl_get_active_pd);
// ----------------

TRACE_EVENT(rx_frame,

	TP_PROTO(u32 pkt_num, u8 last_pkt_num, u8 control),

	TP_ARGS(pkt_num, last_pkt_num, control),

	TP_STRUCT__entry(
		__field(	u32,	pkt_num		)
		__field(	u8,	last_pkt_num	)
		__field(	u8,	control		)
	),

	TP_fast_assign(
		__entry->pkt_num = pkt_num;
		__entry->last_pkt_num = last_pkt_num;
		__entry->control = control;
	),

	TP_printk("RX frame PN=0x%x LPN=0x%x control=0x%x",
		__entry->pkt_num, __entry->last_pkt_num, __entry->control)
);

DECLARE_EVENT_CLASS(rx_elt_class,

	TP_PROTO(u8 type),

	TP_ARGS(type),

	TP_STRUCT__entry(
		__field(	u8,	type	)
	),

	TP_fast_assign(
		__entry->type	= type;
	),

	TP_printk("RX: %s", __print_symbolic(__entry->type, \
		{ OZ_ELT_CONNECT_REQ,		"OZ_ELT_CONNECT_REQ" }, \
		{ OZ_ELT_DISCONNECT,		"OZ_ELT_DISCONNECT" }, \
		{ OZ_ELT_UPDATE_PARAM_REQ,	"OZ_ELT_UPDATE_PARAM_REQ" }, \
		{ OZ_ELT_FAREWELL_REQ,		"OZ_ELT_FAREWELL_REQ" }, \
		{ OZ_ELT_APP_DATA,		"OZ_ELT_APP_DATA" }))
);

#define DEFINE_RX_ELT_EVENT(name) \
DEFINE_EVENT(rx_elt_class, name, \
	TP_PROTO(u8 type), \
	TP_ARGS(type))
DEFINE_RX_ELT_EVENT(rx_elt_connect_req);
DEFINE_RX_ELT_EVENT(rx_elt_disconnect);
DEFINE_RX_ELT_EVENT(rx_elt_update_param_req);
DEFINE_RX_ELT_EVENT(rx_elt_farewell_req);
DEFINE_RX_ELT_EVENT(rx_elt_app_data);
DEFINE_RX_ELT_EVENT(rx_elt_unknown);

TRACE_EVENT(usb_req_get_descriptor,

	TP_PROTO(u8 length, u16 offset, u16 total_size),

	TP_ARGS(length, offset, total_size),

	TP_STRUCT__entry(
		__field(	u8,	length		)
		__field(	u16,	offset		)
		__field(	u16,	total_size	)
	),

	TP_fast_assign(
		__entry->length = length;
		__entry->offset = offset;
		__entry->total_size = total_size;
	),

	TP_printk("USB_REQ_GET_DESCRIPTOR length = %d offs = %d tot_size = %d",
	       __entry->length, __entry->offset, __entry->total_size)
);

TRACE_EVENT(unknown_urb,

	TP_PROTO(void *urb),

	TP_ARGS(urb),

	TP_STRUCT__entry(
		__field(	struct urb*,	urb	)
	),

	TP_fast_assign(
		__entry->urb = urb;
	),

	TP_printk("ERROR Unknown URB %p", __entry->urb)
);

TRACE_EVENT(invalid_endpoint_number,

	TP_PROTO(u8 ep_addr),

	TP_ARGS(ep_addr),

	TP_STRUCT__entry(
		__field(	u8,	ep_addr	)
	),

	TP_fast_assign(
		__entry->ep_addr = ep_addr;
	),

	TP_printk("Invalid endpoitn number %d", __entry->ep_addr)
);

DECLARE_EVENT_CLASS(message_class,

	TP_PROTO(char* message),

	TP_ARGS(message),

	TP_STRUCT__entry(
		__string(	message,	message	)
	),

	TP_fast_assign(
		__assign_str(message, message);
	),

	TP_printk("%s", __get_str(message))
);

#define DEFINE_MESSAGE_EVENT(name) \
DEFINE_EVENT(message_class, name, \
	TP_PROTO(char* message), \
	TP_ARGS(message))
DEFINE_MESSAGE_EVENT(active_pd_arrived);
DEFINE_MESSAGE_EVENT(active_pd_departed);
DEFINE_MESSAGE_EVENT(cdev_claim_ctx_failed);
DEFINE_MESSAGE_EVENT(cdev_create_sysfs_entry_failed);
DEFINE_MESSAGE_EVENT(cdev_register_failed);
DEFINE_MESSAGE_EVENT(cdev_release_ctx);
DEFINE_MESSAGE_EVENT(cdev_service_paused);
DEFINE_MESSAGE_EVENT(cdev_service_resumed);
DEFINE_MESSAGE_EVENT(cdev_service_started);
DEFINE_MESSAGE_EVENT(cdev_service_stopped);
DEFINE_MESSAGE_EVENT(hcd_buffer_full);
DEFINE_MESSAGE_EVENT(ioctl_get_active_pd);
DEFINE_MESSAGE_EVENT(ioctl_get_pd_list);
DEFINE_MESSAGE_EVENT(ioctl_set_active_pd);
DEFINE_MESSAGE_EVENT(ozmo_wpan_class_register_failed);
DEFINE_MESSAGE_EVENT(pd_reset);
DEFINE_MESSAGE_EVENT(rx_usb_req_vendor_class);
DEFINE_MESSAGE_EVENT(urb_buffer_full);
DEFINE_MESSAGE_EVENT(usb_context_dealloc);
DEFINE_MESSAGE_EVENT(usb_context_exists);
DEFINE_MESSAGE_EVENT(usb_hub_null_port);
DEFINE_MESSAGE_EVENT(usb_service_paused);
DEFINE_MESSAGE_EVENT(usb_service_resumed);
DEFINE_MESSAGE_EVENT(usb_service_started);
DEFINE_MESSAGE_EVENT(usb_service_stopped);
DEFINE_MESSAGE_EVENT(usb_service_stopping);

DECLARE_EVENT_CLASS(usb_stream_class,

	TP_PROTO(char* function_name, u8 ep_num),

	TP_ARGS(function_name, ep_num),

	TP_STRUCT__entry(
		__string(	function_name,	function_name	)
		__field(	u8,		ep_num	)
	),

	TP_fast_assign(
		__assign_str(function_name, function_name);
		__entry->ep_num	= ep_num;
	),

	TP_printk("%s: (0x%x)", __get_str(function_name), __entry->ep_num)
);

#define DEFINE_USB_STREAM_EVENT(name) \
DEFINE_EVENT(usb_stream_class, name, \
	TP_PROTO(char* function_name, u8 ep_num), \
	TP_ARGS(function_name, ep_num))
DEFINE_USB_STREAM_EVENT(usb_stream_create);
DEFINE_USB_STREAM_EVENT(usb_stream_delete);

DECLARE_EVENT_CLASS(urb_buffer_class,

	TP_PROTO(char* status, int g_nb_urbs, struct urb *urb),

	TP_ARGS(status, g_nb_urbs, urb),

	TP_STRUCT__entry(
		__string(	status,		status		)
		__field(	int,		g_nb_urbs	)
		__field(	struct urb*,	urb		)
	),

	TP_fast_assign(
		__assign_str(status, status);
		__entry->g_nb_urbs	= g_nb_urbs;
		__entry->urb		= urb;
	),

	TP_printk("%s = %d %p",
		__get_str(status), __entry->g_nb_urbs, __entry->urb);
);

#define DEFINE_URB_BUFFER_EVENT(name) \
DEFINE_EVENT(urb_buffer_class, name, \
	TP_PROTO(char* status, int g_nb_urbs, struct urb *urb), \
	TP_ARGS(status, g_nb_urbs, urb))
DEFINE_URB_BUFFER_EVENT(urb_up);
DEFINE_USB_STREAM_EVENT(urb_down);

DECLARE_EVENT_CLASS(set_pd_state_class,

	TP_PROTO(unsigned state),

	TP_ARGS(state),

	TP_STRUCT__entry(
		__field(	unsigned,	state	)
	),

	TP_fast_assign(
		__entry->state	= state;
	),

	TP_printk("PD State: %s", __print_symbolic(__entry->state, \
		{ OZ_PD_S_IDLE,			"OZ_PD_S_IDLE" }, \
		{ OZ_PD_S_CONNECTED,		"OZ_PD_S_CONNECTED" }, \
		{ OZ_PD_S_STOPPED,		"OZ_PD_S_STOPPED" }, \
		{ OZ_PD_S_SLEEP,		"OZ_PD_S_SLEEP" }))
);

#define DEFINE_SET_PD_STATE_EVENT(name) \
DEFINE_EVENT(set_pd_state_class, name, \
	TP_PROTO(unsigned state), \
	TP_ARGS(state))
DEFINE_SET_PD_STATE_EVENT(set_pd_state_idle);
DEFINE_SET_PD_STATE_EVENT(set_pd_state_connected);
DEFINE_SET_PD_STATE_EVENT(set_pd_state_stopped);
DEFINE_SET_PD_STATE_EVENT(set_pd_state_sleep);

TRACE_EVENT(rx_usb_req,

	TP_PROTO(u8 type),

	TP_ARGS(type),

	TP_STRUCT__entry(
		__field(	u8,	type	)
	),

	TP_fast_assign(
		__entry->type = type;
	),

	TP_printk("RX %s", __print_symbolic(__entry->state, \
		{ USB_REQ_GET_STATUS,		"USB_REQ_GET_STATUS - cnf" }, \
		{ USB_REQ_CLEAR_FEATURE,	"USB_REQ_CLEAR_FEATURE - cnf" }, \
		{ USB_REQ_SET_FEATURE,		"USB_REQ_SET_FEATURE - cnf" }, \
		{ USB_REQ_SET_ADDRESS,		"USB_REQ_SET_ADDRESS - cnf" }, \
		{ USB_REQ_GET_DESCRIPTOR,	"USB_REQ_GET_DESCRIPTOR - cnf" }, \
		{ USB_REQ_SET_DESCRIPTOR,	"USB_REQ_SET_DESCRIPTOR - cnf" }, \
		{ USB_REQ_GET_CONFIGURATION,	"USB_REQ_GET_CONFIGURATION - cnf" }, \
		{ USB_REQ_SET_CONFIGURATION,	"USB_REQ_SET_CONFIGURATION - cnf" }, \
		{ USB_REQ_GET_INTERFACE,	"USB_REQ_GET_INTERFACE - cnf" }, \
		{ USB_REQ_SET_INTERFACE,	"USB_REQ_SET_INTERFACE - cnf" }, \
		{ USB_REQ_SYNCH_FRAME,		"USB_REQ_SYNCH_FRAME - cnf" }))
);

#endif /* _OZWPAN_TRACE_H */

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE ozwpan_trace
#include <trace/define_trace.h>
