# pragma once
# include <Siv3D.hpp>

//
// ���[�e�B���e�B
//
	// �|�C���^�[
	# include "Pointer.hpp"

	// �X���b�h
	# include "Task.hpp"

	// ����L���[
	# include "BlockingQueue.hpp"

	// ���������
	# include "StringArgs.hpp"

	// �A�Z�b�g
	# include "Assets.hpp"

	// ���W�ϊ�
	# include "Coordinate.hpp"

	// �G�t�F�N�g
	# include "Effect.hpp"

	// �Z�[�u�f�[�^
	# include "Savedata.hpp"
//
// �O���t�B�b�N
//
	// �F
	# include "Coloring.hpp"

	// �}�`�̕`��
	# include "Figure.hpp"

	// �f�v�X
	# include "CameraDepth.hpp"

	// ���C���J����
	# include "MainCamera.hpp"
//
// ����
//
	// ����
	# include "DeltaTime.hpp"

	// �C���^�[�o��
	# include "Intervaler.hpp"

	// �����蔻��
	# include "Physics.hpp"

	// PhysicsGroup
	# include "PhysicsGroup.hpp"
//
// �Q�[���I�u�W�F�N�g
//
	// ���[���h
	# include "World.hpp"

	// �G���e�B�e�B
	# include "Entity.hpp"

	// �R���|�[�l���g
	# include "Component.hpp"

	// Transform�R���|�[�l���g
	# include "Transform.hpp"

	// Collider�R���|�[�l���g
	# include "Collider.hpp"

	// BoxCollider�R���|�[�l���g
	# include "BoxCollider.hpp"

	// SlopeCollider�R���|�[�l���g
	# include "SlopeCollider.hpp"

	// Rigidbody�R���|�[�l���g
	# include "Rigidbody.hpp"

	// GraphicsLayer�R���|�[�l���g
	# include "GraphicsLayer.hpp"

	// Updatable�R���|�[�l���g
	# include "Updatable.hpp"

	// Drawable�R���|�[�l���g
	# include "Drawable.hpp"

	// UpdatableDrawer�R���|�[�l���g
	# include "UpdatableDrawer.hpp"

	// UI�R���|�[�l���g
	# include "UI.hpp"

	// UpdatableUI�R���|�[�l���g
	# include "UpdatableUI.hpp"

	// Name�R���|�[�l���g
	# include "Name.hpp"
//
// AI
//
	// �X�e�[�g�}�V��
	# include "StateMachine.hpp"

	// �r�w�C�r�A�c���[
	# include "BehaviourTree.hpp"
//
// �V�X�e��
//
	// �G���W��
	# include "Engine.hpp"

# ifdef _DEBUG
	// �f�o�b�O
	# include "Debug.hpp"
# endif

# ifndef NO_CRE_USING
	using namespace cre;
# endif
