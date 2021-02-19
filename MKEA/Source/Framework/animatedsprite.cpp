#include "animatedsprite.h"

// Local includes:
#include "texture.h"
#include "backbuffer.h"

#include <SDL.h>

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.0f)
	, m_frameWidth(0)
	, m_timeElapsed(0.0f)
	, m_currentFrame(0)
	, m_paused(false)
	, m_loop(false)
	, m_animating(false)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Texture& texture)
{
	// TODO remove hard coded values!
	m_frameWidth = 0;
	m_frameSpeed = 0;

	m_loop = false;
	m_paused = false;
	m_animating = true;

	Sprite::Initialise(texture);

	StartAnimating();

	return (true);
}

void
AnimatedSprite::Process(float deltaTime)
{
	// SS04.10: If not paused...
	if (!m_paused)
	{
		if (m_animating)
		{
			// SS04.10: Count the time elapsed.
			m_timeElapsed += deltaTime;

			// SS04.10: If the time elapsed is greater than the frame speed.
			if (m_timeElapsed > m_frameSpeed)
			{
				// SS04.10: Reset the time elapsed counter.
				m_timeElapsed = 0.0f;
				// SS04.10: Move to the next frame.
				m_currentFrame++;

				// SS04.10: If the current frame is greater than the number of frame in this animation...
				if (m_currentFrame >= static_cast<int>(m_frameCoordinates.size()))
				{
					// SS04.10: Reset to the first frame.
					m_currentFrame = 0;

					if (!m_loop)
					{
						// SS04.10: Stop the animation if it is not looping...
						m_animating = false;
					}
				}
			}
		}
	}
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	// SS04.10: Draw the particular frame into the backbuffer.
	backbuffer.DrawAnimatedSprite(*this);
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::Pause()
{
	m_paused = !m_paused;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_currentFrame = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

int
AnimatedSprite::GetFrameWidth() const
{
	return (m_frameWidth);
}

void
AnimatedSprite::AddFrame(int x)
{
	// SS04.10: Add the x coordinate to the frame coordinate container.
	m_frameCoordinates.push_back(x);
}

int
AnimatedSprite::GetCurrentFrame() const
{
	return m_currentFrame;
}