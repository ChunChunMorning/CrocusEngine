# include "../Engine.hpp"
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "../Entity.hpp"
# include "ColliderManager.hpp"
# include "DebugManager.hpp"
# include "DrawableManager.hpp"
# include "GraphicsLayerManager.hpp"
# include "LoaderManager.hpp"
# include "MainCameraManager.hpp"
# include "NameManager.hpp"
# include "RigidbodyManager.hpp"
# include "TimeManager.hpp"
# include "UIManager.hpp"
# include "UpdatableManager.hpp"

namespace cre
{
	Engine* Engine::m_instance = nullptr;

	Engine::Engine() :
# ifdef _DEBUG
		m_debug(std::make_unique<DebugManager>()),
# endif
		m_time(std::make_unique<TimeManager>()),
		m_camera(std::make_unique<MainCameraManager>()),
		m_entity(Entity::Create()),
		m_loader(std::make_unique<LoaderManager>()),
		m_collider(std::make_unique<ColliderManager>()),
		m_rigidbody(std::make_unique<RigidbodyManager>()),
		m_layer(std::make_unique<GraphicsLayerManager>()),
		m_updatable(std::make_unique<UpdatableManager>()),
		m_drawable(std::make_unique<DrawableManager>()),
		m_ui(std::make_unique<UIManager>()),
		m_name(std::make_unique<NameManager>())
	{
		assert(m_instance == nullptr);

		m_instance = this;
	}

	Engine::~Engine()
	{
		assert(m_instance != nullptr);

		m_entity.reset();
		m_instance = nullptr;
	}

	void Engine::update()
	{
		m_time->update();
		m_entity->update();
		m_loader->update();
		m_collider->erase();
		m_layer->erase();
		m_rigidbody->update();

		if (DeltaTime::GetTimeScale() != 0)
		{
			m_rigidbody->escape();
			m_updatable->update();
			m_camera->update();
		}

		m_drawable->update();
		m_ui->update();
	}

	void Engine::addLoader(const FilePath& path)
	{
		m_loader->add(path);
	}

	void Engine::addFactory(const String& name, const Factory& factory)
	{
		m_loader->addFactory(name, factory);
	}

	bool Engine::notYet() const
	{
		return m_loader->notYet();
	}

	void Engine::draw() const
	{
		{
			const auto ct = m_camera->createTransformer();
			const auto wt = ScalableWindow::CreateTransformer();

			m_drawable->draw();

# ifdef _DEBUG
			if (m_debug->isActive())
			{
				m_debug->drawGrid();
				m_layer->draw();
				m_collider->draw();
				m_rigidbody->draw();
			}
			m_debug->draw();
#endif
		}

		const auto wt = ScalableWindow::CreateTransformer();

		m_ui->draw();
	}

# ifdef _DEBUG
	stupid_ptr<DebugManager> Engine::GetDebug()
	{
		assert(m_instance != nullptr);

		return m_instance->m_debug;
	}
# endif

	stupid_ptr<TimeManager> Engine::GetTime()
	{
		assert(m_instance != nullptr);

		return m_instance->m_time;
	}

	stupid_ptr<MainCameraManager> Engine::GetCamera()
	{
		assert(m_instance != nullptr);

		return m_instance->m_camera;
	}

	stupid_ptr<Entity> Engine::GetEntity()
	{
		assert(m_instance != nullptr);

		return m_instance->m_entity;
	}

	stupid_ptr<LoaderManager> Engine::GetLoader()
	{
		assert(m_instance != nullptr);

		return m_instance->m_loader;
	}

	stupid_ptr<ColliderManager> Engine::GetCollider()
	{
		assert(m_instance != nullptr);

		return m_instance->m_collider;
	}

	stupid_ptr<RigidbodyManager> Engine::GetRigidbody()
	{
		assert(m_instance != nullptr);

		return m_instance->m_rigidbody;
	}

	stupid_ptr<GraphicsLayerManager> Engine::GetLayer()
	{
		assert(m_instance != nullptr);

		return m_instance->m_layer;
	}

	stupid_ptr<UpdatableManager> Engine::GetUpdatable()
	{
		assert(m_instance != nullptr);

		return m_instance->m_updatable;
	}

	stupid_ptr<DrawableManager> Engine::GetDrawable()
	{
		assert(m_instance != nullptr);

		return m_instance->m_drawable;
	}

	stupid_ptr<UIManager> Engine::GetUI()
	{
		assert(m_instance != nullptr);

		return m_instance->m_ui;
	}

	stupid_ptr<NameManager> Engine::GetName()
	{
		assert(m_instance != nullptr);

		return m_instance->m_name;
	}
}
