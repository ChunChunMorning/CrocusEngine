# pragma once
# include <Siv3D.hpp>

//
// ユーティリティ
//
	// ポインター
	# include "Pointer.hpp"

	// スレッド
	# include "Task.hpp"

	// 並列キュー
	# include "BlockingQueue.hpp"

	// 文字列引数
	# include "StringArgs.hpp"

	// アセット
	# include "Assets.hpp"

	// 座標変換
	# include "Coordinate.hpp"

	// エフェクト
	# include "Effect.hpp"

	// セーブデータ
	# include "Savedata.hpp"
//
// グラフィック
//
	// 色
	# include "Coloring.hpp"

	// 図形の描画
	# include "Figure.hpp"

	// デプス
	# include "CameraDepth.hpp"

	// メインカメラ
	# include "MainCamera.hpp"
//
// 物理
//
	// 時間
	# include "DeltaTime.hpp"

	// インターバル
	# include "Intervaler.hpp"

	// 当たり判定
	# include "Physics.hpp"

	// PhysicsGroup
	# include "PhysicsGroup.hpp"
//
// ゲームオブジェクト
//
	// ワールド
	# include "World.hpp"

	// エンティティ
	# include "Entity.hpp"

	// コンポーネント
	# include "Component.hpp"

	// Transformコンポーネント
	# include "Transform.hpp"

	// Colliderコンポーネント
	# include "Collider.hpp"

	// BoxColliderコンポーネント
	# include "BoxCollider.hpp"

	// SlopeColliderコンポーネント
	# include "SlopeCollider.hpp"

	// Rigidbodyコンポーネント
	# include "Rigidbody.hpp"

	// GraphicsLayerコンポーネント
	# include "GraphicsLayer.hpp"

	// Updatableコンポーネント
	# include "Updatable.hpp"

	// Drawableコンポーネント
	# include "Drawable.hpp"

	// UpdatableDrawerコンポーネント
	# include "UpdatableDrawer.hpp"

	// UIコンポーネント
	# include "UI.hpp"

	// UpdatableUIコンポーネント
	# include "UpdatableUI.hpp"

	// Nameコンポーネント
	# include "Name.hpp"
//
// AI
//
	// ステートマシン
	# include "StateMachine.hpp"

	// ビヘイビアツリー
	# include "BehaviourTree.hpp"
//
// システム
//
	// エンジン
	# include "Engine.hpp"

# ifdef _DEBUG
	// デバッグ
	# include "Debug.hpp"
# endif

# ifndef NO_CRE_USING
	using namespace cre;
# endif
