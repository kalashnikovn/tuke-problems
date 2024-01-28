#include <stdio.h>
#include <stdlib.h>
#include "world.h"

struct container* create_world() {
    // Room
    struct room* room = create_room("room", "room");
    struct item* phone = create_item("iPhone", "phone", USABLE | MOVABLE);
    struct item* backpack = create_item("Backpack", "Backpack", USABLE | MOVABLE | OPENABLE);
    struct item* clothes = create_item("Clothes", "Clothes", USABLE);
    add_item_to_room(room, phone);
    add_item_to_room(room, backpack);
    add_item_to_room(room, clothes);

    struct container* world = create_container(NULL, ROOM, room);

    struct room* hall = create_room("hall", "hall");

    struct room* toilet = create_room("toilet", "toilet");

    struct room* bathroom = create_room("bathroom", "bathroom");
    struct item* item = create_item("toothbrush", "toothbrush", USABLE);
    add_item_to_room(bathroom, item);

    struct room* living_room = create_room("living room", "living room");

    struct room* elevator = create_room("elevator", "elevator");

    struct room* street = create_room("street", "street");

    struct room* bus_stop = create_room("bus stop", "bus stop");
    struct item* ticket = create_item("Ticket", "Ticket", USABLE);
    add_item_to_room(bus_stop, ticket);


    struct room* bus = create_room("bus", "bus");


    struct room* university = create_room("university", "university");


    struct room* lesson = create_room("lesson", "lesson");


    struct room* library = create_room("library", "library");


    struct room* canteen = create_room("canteen", "canteen");


    struct room* shop = create_room("shop", "shop");


    struct room* park = create_room("park", "park");


    struct room* gym = create_room("gym", "gym");

    // Set Exits Rooms
    set_exits_from_room(room, living_room, NULL, NULL, NULL);
    set_exits_from_room(living_room, hall, room, bathroom, toilet);
    set_exits_from_room(bathroom, NULL, living_room, NULL, NULL);
    set_exits_from_room(toilet, NULL, living_room, NULL, NULL);
    set_exits_from_room(hall, elevator, living_room, gym, NULL);
    set_exits_from_room(elevator, street, hall, NULL, NULL);
    set_exits_from_room(gym, NULL, hall, NULL, NULL);
    set_exits_from_room(street, bus_stop, elevator, shop, park);
    set_exits_from_room(shop, NULL, street, NULL, NULL);
    set_exits_from_room(park, NULL, street, NULL, NULL);
    set_exits_from_room(bus_stop, bus, street, NULL, NULL);
    set_exits_from_room(bus, university, bus_stop, NULL, NULL);
    set_exits_from_room(university, lesson, bus, library, canteen);
    set_exits_from_room(lesson, NULL, university, NULL, NULL);
    set_exits_from_room(library, NULL, university, NULL, NULL);
    set_exits_from_room(canteen, NULL, university, NULL, NULL);

    // Add Rooms to World;
    add_room_to_world(world, room);
    add_room_to_world(world, living_room);
    add_room_to_world(world, toilet);
    add_room_to_world(world, bathroom);
    add_room_to_world(world, hall);
    add_room_to_world(world, elevator);
    add_room_to_world(world, gym);
    add_room_to_world(world, street);
    add_room_to_world(world, shop);
    add_room_to_world(world, park);
    add_room_to_world(world, bus_stop);
    add_room_to_world(world, bus);
    add_room_to_world(world, university);
    add_room_to_world(world, lesson);
    add_room_to_world(world, library);
    add_room_to_world(world, canteen);

    return world;
};

struct container* destroy_world(struct container* world) {
    return destroy_containers(world);
}

struct container* add_room_to_world(struct container* world, struct room* room) {
    if(room == NULL || get_from_container_by_name(world, room->name) != NULL) {
        return NULL;
    }

    struct container* new_container = create_container(world, ROOM, room);

    return new_container;
}

struct room* get_room(struct container* world, char* name) {
    if(world == NULL || name == NULL) {
        return NULL;
    }

    struct room* room = get_from_container_by_name(world, name);

    return room;
}