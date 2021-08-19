A programm to be run on a node so that it connect to one specified node upstream, accept any number of connections from downstream, and copy information sent from upstream to downstream.

We should have a main function taking the address to connect to, performing 
argument checking, and error recovery, and delegating to a Distributor class.

The distributor class should own the I/O ressources. It should first connect upstream,
then start an acceptor to connect downstream, keeping any incoming connection open
and tracked. Then it should receive from upstream, writing to a buffer, and then
write the buffer to each outgoing connection. Buffer management should prioritize
writing to the buffer if full.

Potential implementation:
- as one single-threader I/O context, with appropriate handlers, or with 
a coroutine.
- as a multi-threaded pool for a single I/O context, taking care of the strands.
- as a multi-threades multi-I/O pool, one for each connection.

The reading sequence should be: create a ref-counted buffer; read from upstream
into it; start writes operations for each of the downstream connections from 
that buffer; and let the reference count destroy the buffer once it has been read
too.
