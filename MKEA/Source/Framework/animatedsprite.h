#include "sprite.h"
#include <vector>

class BackBuffer;
class Texture;

class AnimatedSprite : public Sprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Texture& texture);
	void AddFrame(int x);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetFrameSpeed(float f);
	void SetFrameWidth(int w);
	int GetFrameWidth() const;
	int GetCurrentFrame() const;

	void Pause();
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

protected:

private:
	AnimatedSprite(const AnimatedSprite& animatedSprite);
	AnimatedSprite& operator=(const AnimatedSprite& animatedSprite);
	// Fields:
public:

protected:
	// SS04.10: Add a field, the container for frame coordinates.
	std::vector<int> m_frameCoordinates;

	float m_frameSpeed;
	int m_frameWidth;

	float m_timeElapsed;
	int m_currentFrame;

	bool m_paused;
	bool m_loop;
	bool m_animating;

private:

};