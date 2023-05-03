#include "g_local.h"

void attack_think(edict_t* self) {

	vec3_t forward;
	vec3_t start;

	VectorSet(self->s.origin, self->owner->s.origin[0]+(rand()%30 +10), self->owner->s.origin[1]+5, 20);
	VectorSet(self->s.angles, 0, self->owner->s.angles[1], 0);
	VectorSet(start, self->s.origin[0], self->s.origin[1], self->owner->s.origin[2]);
	AngleVectors(self->s.angles, forward, NULL, NULL);
	if (((self->owner->client->latched_buttons | self->owner->client->buttons) & BUTTON_ATTACK))
		fire_blaster(self->owner, start, forward, 100, 800, EF_BLASTER, MOD_TARGET_BLASTER);
	gi.linkentity(self);
	gi.linkentity(self->owner);


}

void Spawn_Chicken(edict_t* powerup, edict_t* ent) {

	edict_t* chicken;

	chicken = G_Spawn();
	chicken->owner = ent;
	chicken->solid = SOLID_NOT;
	chicken->movetype = MOVETYPE_FLYMISSILE;
	chicken->prethink = attack_think;
	chicken->classname = "chickenpowerup";
	chicken->s.modelindex = gi.modelindex("models/monsters/soldier/tris.md2");
	VectorClear(chicken->mins);
	VectorClear(chicken->maxs);
	VectorCopy(ent->s.angles, chicken->s.angles);
	VectorSet(chicken->s.origin, ent->s.origin[0]+5, ent->s.origin[1]+5, 50);
	chicken->nextthink = level.time + 30;
	chicken->think = G_FreeEdict;
	gi.linkentity(chicken);

}
