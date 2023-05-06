#include "g_local.h"

void c_think(edict_t *self) {

	vec3_t forward, right, up, angles;
	vec3_t spot1, spot2, dir;
		
	self->nextthink = level.time + FRAMETIME;
	VectorSet(self->s.origin, self->owner->s.origin[0], self->owner->s.origin[1], 190);
	gi.linkentity(self);
	gi.linkentity(self->owner);

}

void PlayerView(edict_t* ent)
{
	vec3_t angles;
	
	if (!ent->client->playerModelv->client)
		ent->client->playerModelv->client = ent->client;
	
	if ((ent->client->camflag == 1) && (ent->client->playerModelv))
	{
		ent->client->playerModelv->s = ent->s; 
		gi.linkentity(ent->client->playerModelv);
	}
}

void topCam(edict_t* ent)
{

	ent->client->camflag = 1;

	edict_t* cam;

	cam = G_Spawn();
	cam->owner = ent;
	cam->solid = SOLID_NOT;
	cam->movetype = MOVETYPE_FLYMISSILE;
	cam->prethink = c_think;
	ent->client->cam = cam;
	cam->classname = "chasecam";
	//cam->s.modelindex = gi.modelindex("models/monsters/soldier/tris.md2");
	VectorClear(cam->mins);
	VectorClear(cam->maxs);
	ent->client->ps.gunindex = 0;

	VectorCopy(ent->s.angles, cam->s.angles);
	VectorSet(cam->s.origin, ent->s.origin[0], ent->s.origin[1], 180);
	ent->client->playerModelv = G_Spawn();
	PlayerView(ent);
	gi.linkentity(cam);
	gi.linkentity(ent);

}


void normalCam(edict_t* ent)
{
	ent->client->camflag = 0;
	G_FreeEdict(ent->client->cam);
	G_FreeEdict(ent->client->playerModelv);
	ent->client->cam = NULL;
	ent->client->playerModelv = NULL;
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
