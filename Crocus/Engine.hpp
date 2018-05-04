# pragma once
# include <Siv3D.hpp>
# include "Assets.hpp"
# include "Component.hpp"
# include "Intervaler.hpp"
# include "Pointer.hpp"

namespace cre
{
# ifdef _DEBUG
	class DebugManager;
# endif
	class TimeManager;
	class MainCameraManager;
	class Entity;
	class LoaderManager;
	class ColliderManager;
	class RigidbodyManager;
	class GraphicsLayerManager;
	class UpdatableManager;
	class DrawableManager;
	class UIManager;
	class NameManager;

	using Factory = std::function<unique_ptr<Component>(const XMLElement&, const Assets&)>;

	class Engine
	{
	private:

# ifdef _DEBUG
		unique_ptr<DebugManager> m_debug;
# endif

		unique_ptr<TimeManager> m_time;

		unique_ptr<MainCameraManager> m_camera;

		unique_ptr<Entity> m_entity;

		unique_ptr<LoaderManager> m_loader;

		unique_ptr<ColliderManager> m_collider;

		unique_ptr<RigidbodyManager> m_rigidbody;

		unique_ptr<GraphicsLayerManager> m_layer;

		unique_ptr<UpdatableManager> m_updatable;

		unique_ptr<DrawableManager> m_drawable;

		unique_ptr<UIManager> m_ui;

		unique_ptr<NameManager> m_name;

		static Engine* m_instance;

		Engine(const Engine&) = delete;
		Engine& operator =(const Engine&) = delete;

	public:

		Engine();

		~Engine();

		void update();

		void addLoader(const FilePath& path);

		void addFactory(const String& name, const Factory& factory);

		bool notYet() const;

		void draw() const;

# ifdef _DEBUG
		static stupid_ptr<DebugManager> GetDebug();
# endif

		static stupid_ptr<TimeManager> GetTime();

		static stupid_ptr<MainCameraManager> GetCamera();

		static stupid_ptr<Entity> GetEntity();

		static stupid_ptr<LoaderManager> GetLoader();

		static stupid_ptr<ColliderManager> GetCollider();

		static stupid_ptr<RigidbodyManager> GetRigidbody();

		static stupid_ptr<GraphicsLayerManager> GetLayer();

		static stupid_ptr<UpdatableManager> GetUpdatable();

		static stupid_ptr<DrawableManager> GetDrawable();

		static stupid_ptr<UIManager> GetUI();

		static stupid_ptr<NameManager> GetName();
	};
}
