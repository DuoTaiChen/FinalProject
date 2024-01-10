#ifndef LIGHTNING_H_INCLUDE
#define LIGHTNING_H_INCLUDE

#include"Global.h"
enum class LightningState
{
	PREVIEW,
	TRIGGER,
	END
};

class Lightning
{
public:
	Lightning();
	~Lightning();
	LightningState GetState() { return state; };
	bool GetShoot() { return shoot; }
	void Update();
	void Draw();
	bool IsCollision(int characterX);
private:
	void Init();
	void Destroy();
	int x;
	LightningState state;
	int previewCounter;
	int triggerCounter;
	bool shoot;
};

#endif