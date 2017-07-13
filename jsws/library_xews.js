var library = {
	$xews: { sockets: {} },
	xews_connect: function (client, uri, onMessage, onConnected) {
		var socket = new WebSocket(Pointer_stringify(uri));
		xews.sockets[client] = socket;

		socket.onmessage = function (event) {
			debugger;
			console.log("Got a message", event.data);
			Runtime.dynCall("vi", onMessage, [client]);
		};

		socket.onopen = function (event) {
			console.log("Connection opened");
			Runtime.dynCall("vi", onConnected, [client]);
		};
	},
	xews_send: function (client, data, size) {
		debugger;
		var socket = xews.sockets[client];
		if (socket && socket.readyState === 'OPEN') {
			var bytes = {{{ makeHEAPView('U8', 'data', 'data + size') }}}; //new Uint8Array();
			debugger;
			socket.send(bytes);
		}
	},
	xews_close: function (client) {
		var socket = xews.sockets[client];
		if (socket) {
			socket.close();
			delete xews.sockets[client];
		}
	},
	xews_move: function (oldClient, newClient) {
		var socket = xews.sockets[oldClient];
		if (socket) {
			xews.sockets[newClient] = socket;
			delete xews.sockets[oldClient];
		}
	}
};

autoAddDeps(library, "$xews");

mergeInto(LibraryManager.library, library);
