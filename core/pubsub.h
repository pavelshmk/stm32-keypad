//
// Created by bakatrouble on 06/11/22.
//

#ifndef HAL_PUBSUB_H
#define HAL_PUBSUB_H

typedef void (*PubSubCallback)(const void *message, void *ctx);
typedef struct PubSub PubSub;
typedef struct PubSubSubscription PubSubSubscription;

PubSub *pubsub_alloc();
void pubsub_destroy(PubSub *pubsub);
PubSubSubscription *pubsub_subscribe(PubSub *pubsub, PubSubCallback callback, void *ctx);
void pubsub_unsubscribe(PubSub *pubsub, PubSubSubscription *sub);
void pubsub_publish(PubSub *pubsub, void *message);

#endif //HAL_PUBSUB_H
