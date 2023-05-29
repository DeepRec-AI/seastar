# SeaStar

## Introduction

SeaStar is an event-driven framework allowing you to write non-blocking,
asynchronous code in a relatively straightforward manner (once understood).
It is based on [futures](http://en.wikipedia.org/wiki/Futures_and_promises).

SeaStar is used in GRPC++ and StarServer protocols in DeepRec. New features in SeaStar:
-   Add seastar::packet_queue & seastar::channel to pass packets to seastar threads.
-   Support read_exactly read into buffer which allocate by user.
-   Disable seastar signals logic which would affect TensorFlow's behavior.
-   Support disconnection handling when send/recv errors happen.

## Building SeaStar

SeaStar is built as a third-party source code in DeepRec. By default, SeaStar is enabled in DeepRec.

More features built on SeaStar:

* [GRPC++](https://github.com/DeepRec-AI/DeepRec/blob/main/docs/docs_en/GRPC%2B%2B.md)
* [StarServer](https://github.com/DeepRec-AI/DeepRec/blob/main/docs/docs_en/StarServer.md)
