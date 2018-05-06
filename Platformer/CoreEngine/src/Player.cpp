#include  "stdafx.h"

#include <Player.h>
#include <Input.h>


using  namespace CoreEngineNS;

Player::~Player()
{
}

void Player::Awake()
{
	std::cout << "Player Alive" << std::endl;
	transform = &this->GetComponent<Transform>();
	m_movementSpeed = 0.2f;
}

void Player::Update()
{
	if (Input::GetMovementDirection().x > 0)
		transform->SetPositionX(transform->GetPosition().x + m_movementSpeed);
		
	if (Input::GetMovementDirection().x < 0)
		transform->SetPositionX(transform->GetPosition().x - m_movementSpeed);
		
	if (Input::GetMovementDirection().y < 0)
		transform->SetPositionY(transform->GetPosition().y + m_movementSpeed);
		

	if (Input::GetMovementDirection().y > 0)
		transform->SetPositionY(transform->GetPosition().y - m_movementSpeed);
}
