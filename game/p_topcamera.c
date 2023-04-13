#include "g_local.h"

void c_think(edict_t *self) {

	

	gi.cprintf(self->owner, PRINT_HIGH, "cam origin  %f      %f       %f\n", self->s.origin[0], self->s.origin[1], self->s.origin[2]);
	gi.cprintf(self->owner, PRINT_HIGH, "origin  %f      %f       %f\n", self->owner->s.origin[0], self->owner->s.origin[1], self->owner->s.origin[2]);
	gi.linkentity(self);
	gi.linkentity(self->owner);


}

void topCam(edict_t* ent)
{

	ent->client->camflag = 1;

	edict_t* cam;

	cam = G_Spawn();
	cam->owner = ent;
	cam->solid = SOLID_BBOX;
	cam->movetype = MOVETYPE_FLYMISSILE;
	cam->prethink = c_think;
	ent->client->cam = cam;
	cam->classname = "chasecam";
	//cam->s.modelindex = gi.modelindex("models/monsters/soldier/tris.md2");
	VectorClear(cam->mins);
	VectorClear(cam->maxs);
	ent->client->ps.gunindex = 0;



	VectorCopy(ent->s.angles, cam->s.angles);
	VectorCopy(ent->mins,cam->mins);
	VectorCopy(ent->maxs,cam->maxs);

	VectorSet(cam->s.origin, ent->s.origin[0] * 1.2, ent->s.origin[1] * 1.2, 130);

	gi.linkentity(cam);
	gi.linkentity(ent);

}


void normalCam(edict_t* ent)
{
	ent->client->camflag = 0;
	G_FreeEdict(ent->client->cam);
	ent->client->ps.gunindex = gi.modelindex(ent->client->pers.weapon->view_model);

}

void Cmd_topdownCam(edict_t *ent) {

	if (ent->client->camflag)
	{
		normalCam(ent);
	}
	else
	{
		topCam(ent);
	}

}
