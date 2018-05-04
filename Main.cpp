# include <Siv3D.hpp>
# include "Crocus/Crocus.hpp"



void Main()
{
	Engine engine;

	while (System::Update())
	{
		engine.update();

		engine.draw();
	}
}
