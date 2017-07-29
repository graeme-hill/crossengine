var library = {
	$xews: {
		sockets: {},
		aliases: {},
		resolveClient: function(client) {
			if (client === null || client === undefined) {
				return null;
			} else if (client in this.sockets) {
				return client;
			} else {
				var alias = this.aliases[client];
				return this.resolveClient(alias);
			}
		}
	},

	xews_connect: function (client, uri, onMessage, onConnected) {
		var socket = new WebSocket(Pointer_stringify(uri));
		xews.sockets[client] = socket;

		socket.onmessage = function (event) {
			var reader = new FileReader();
			var currentClient = xews.resolveClient(client);
			reader.addEventListener("loadend", function () {
				var stack = null;
				if (!stack) stack = Runtime.stackSave();

				var buffer = reader.result;
				var typedArray = new Uint8Array(buffer, 0, buffer.byteLength);
				var mem = Runtime.stackAlloc(typedArray.length);
				var size = typedArray.length;

				writeArrayToMemory(typedArray, mem);
				Runtime.dynCall(
					"viii", onMessage, [currentClient, mem, size]);

				if (stack) Runtime.stackRestore(stack);
			});
			reader.readAsArrayBuffer(event.data);
		};

		socket.onopen = function (event) {
			var currentClient = xews.resolveClient(client);
			Runtime.dynCall("vi", onConnected, [currentClient]);
		};
	},

	xews_send: function (client, data, size) {
		var socket = xews.sockets[client];
		if (socket && socket.readyState === 1) {
			var bytes = {{{ makeHEAPView('U8', 'data', 'data + size') }}};
			socket.send(bytes);
		}
	},

	xews_close: function (client) {
		// close and remove the socket
		var socket = xews.sockets[client];
		if (socket) {
			socket.close();
			delete xews.sockets[client];
		}

		// clean up any aliases for this socket
		var clientAliases = Object.keys(xews.aliases);
		for (var i = 0; i < clientAliases.length; i++) {
			var key = clientAliases[i];
			if (xews.aliases[key] === client) {
				delete xews.aliases[key];
			}
		}
	},

	xews_move: function (oldClient, newClient) {
		var socket = xews.sockets[oldClient];
		if (socket) {
			xews.sockets[newClient] = socket;
			delete xews.sockets[oldClient];
			xews.aliases[oldClient] = newClient;
		}
	}
};

autoAddDeps(library, "$xews");

mergeInto(LibraryManager.library, library);
