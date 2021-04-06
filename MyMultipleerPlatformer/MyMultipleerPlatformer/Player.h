
#define PlayerSizeX 0.9
#define PlayerSizeY 1.8

void PlayerReSpawn();
void PlayerDraw();
void PlayerUpdate();
void PlayerPhysiñUpdate();
void DebugDraw(float x, float y, float w, float h, float r, float g, float b);
void Collision(int collisDir);// 1-test by x 0- test by y