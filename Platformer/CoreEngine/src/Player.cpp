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
	{
		transform->SetPosition(glm::vec3(transform->GetPosition().x + m_movementSpeed, transform->GetPosition().y, transform->GetPosition().z));
	}
		
		//gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x + 0.2f, gameObject->GetComponent<Transform>().GetPosition().y, 0));

	if (Input::GetMovementDirection().x < 0)
		transform->SetPosition(glm::vec3(transform->GetPosition().x - m_movementSpeed, transform->GetPosition().y, transform->GetPosition().z));
		//gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x - 0.2f, gameObject->GetComponent<Transform>().GetPosition().y, 0));

	if (Input::GetMovementDirection().y < 0)
		transform->SetPosition(glm::vec3(transform->GetPosition().x, transform->GetPosition().y + m_movementSpeed, transform->GetPosition().z));
		//gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x, gameObject->GetComponent<Transform>().GetPosition().y + 0.2f, 0));

	if (Input::GetMovementDirection().y > 0)
		transform->SetPosition(glm::vec3(transform->GetPosition().x, transform->GetPosition().y - m_movementSpeed, transform->GetPosition().z));
		//gameObject->GetComponent<Transform>().SetPosition(glm::vec3(gameObject->GetComponent<Transform>().GetPosition().x, gameObject->GetComponent<Transform>().GetPosition().y - 0.2f, 0));
}
