//
// Created by bakatrouble on 06/11/22.
//

#include "pubsub.h"
#include <m-list.h>

struct PubSubSubscription {
    PubSubCallback callback;
    void* callback_context;
};

LIST_DEF(PubSubSubscriptionList, PubSubSubscription, M_POD_OPLIST)

struct PubSub {
    PubSubSubscriptionList_t items;
};

PubSub *pubsub_alloc() {
    PubSub *pubsub = malloc(sizeof(PubSub));
    PubSubSubscriptionList_init(pubsub->items);
    return pubsub;
}

void pubsub_destroy(PubSub *pubsub) {
    PubSubSubscriptionList_clear(pubsub->items);
    free(pubsub);
}

PubSubSubscription *pubsub_subscribe(PubSub *pubsub, PubSubCallback callback, void *ctx) {
    PubSubSubscription *sub = PubSubSubscriptionList_push_raw(pubsub->items);
    sub->callback = callback;
    sub->callback_context = ctx;
    return sub;
}

void pubsub_unsubscribe(PubSub *pubsub, PubSubSubscription *sub) {
    PubSubSubscriptionList_it_t it;
    for (PubSubSubscriptionList_it(it, pubsub->items); !PubSubSubscriptionList_end_p(it); PubSubSubscriptionList_next(it)) {
        const PubSubSubscription* item = PubSubSubscriptionList_cref(it);
        if (item == sub) {
            PubSubSubscriptionList_remove(pubsub->items, it);
            break;
        }
    }
}

void pubsub_publish(PubSub *pubsub, void *message) {
    PubSubSubscriptionList_it_t it;
    for (PubSubSubscriptionList_it(it, pubsub->items); !PubSubSubscriptionList_end_p(it); PubSubSubscriptionList_next(it)) {
        const PubSubSubscription* item = PubSubSubscriptionList_cref(it);
        item->callback(message, item->callback_context);
    }
}


