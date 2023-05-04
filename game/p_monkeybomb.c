#include "g_local.h"

void explode_think(edict_t* self) {

	func_explosive_explode(self, self, self->owner, 100, NULL);

}

void sound(edict_t* self)
{
	edict_t* monster;
	
	monster = NULL;
	while ((monster = G_Find(monster, FOFS(classname), "monster_berserk")) != NULL)
	{
		monster->activator = self;
		monster->movetarget = self;
		monster->enemy = self;
		VectorCopy(self->s.origin, monster->movedir);

		gi.linkentity(monster);
	}
	
	//gi.sound(self, CHAN_VOICE, gi.soundindex("plats/pt1_end.wav"), 1, ATTN_NORM, 0);
}

void Spawn_Monkey(vec3_t origin, edict_t* ent) {

	edict_t* monkey;

	monkey = G_Spawn();
	monkey->owner = ent;
	monkey->solid = SOLID_BBOX;
	monkey->movetype = MOVETYPE_NONE;
	//monkey->prethink = sound;
	monkey->classname = "monkeypowerup";
	monkey->s.modelindex = gi.modelindex("models/monsters/soldier/tris.md2");
	monkey->dmg = 100;
	monkey->prethink = sound;
	VectorClear(monkey->mins);
	VectorClear(monkey->maxs);
	VectorCopy(origin, monkey->s.origin);
	monkey->nextthink = level.time + 10;
	monkey->think = explode_think;


	gi.linkentity(monkey);


}
