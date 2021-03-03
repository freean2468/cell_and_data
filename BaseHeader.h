////////////////////////////////////////////////////
// Engine에서 제공하는 모든 헤더파일 선언
////////////////////////////////////////////////////
#ifndef _BaseHeader_H_
#define _BaseHeader_H_

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "strmbasd.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "strmbase.lib")

#include "./Engine_System\SystemDefines.h"

// Utils
#include "./Engine_Misc\Utils.h"
#include "./Engine_Misc\StreamUtilityFunctions.h"
#include "./Engine_Misc\WindowUtils.h"
#include "./Engine_Misc\dsutil.h"
#include "./Engine_Misc\dxutil.h"
#include "./Engine_Misc\DirectUtils.h"

// Math&Physics 부분
#include "./Engine_Math&Physics\Vector2D.h"
#include "./Engine_Math&Physics\Matrix3X3.h"
#include "./Engine_Math&Physics\Matrix4X4.h"
#include "./Engine_Math&Physics\Transformation.h"
#include "./Engine_Math&Physics\Geometry.h"
#include "./Engine_Math&Physics\Rectangle.h"

// Misc 부분
#include "./Engine_Misc\RuntimeCmp.h"
#include "./Engine_Misc\Cgdi.h"
#include "./Engine_Misc\Smoother.h"
#include "./Engine_Misc\Box3D.h"
#include "./Engine_Misc\CellSpaceOfPartition.h"

// Resource 부분
#include "./Side Engine\resource.h"

// Data Structures 부분
#include "./Engine_Data Structures\MyString.h"
#include "./Engine_Data Structures\Array.h"
#include "./Engine_Data Structures\Array2D.h"
#include "./Engine_Data Structures\Array3D.h"
#include "./Engine_Data Structures\Bitvector.h"
#include "./Engine_Data Structures\SListNode.h"
#include "./Engine_Data Structures\SLinkedList.h"
#include "./Engine_Data Structures\SListIterator.h"
#include "./Engine_Data Structures\DListNode.h"
#include "./Engine_Data Structures\DLinkedList.h"
#include "./Engine_Data Structures\DListIterator.h"
#include "./Engine_Data Structures\AStack.h"
#include "./Engine_Data Structures\LStack.h"
#include "./Engine_Data Structures\AQueue.h"
#include "./Engine_Data Structures\LQueue.h"
#include "./Engine_Data Structures\HashEntry.h"
#include "./Engine_Data Structures\Tree.h"
#include "./Engine_Data Structures\TreeIterator.h"
#include "./Engine_Data Structures\BinaryTree.h"
#include "./Engine_Data Structures\BinarySearchTree.h"
#include "./Engine_Data Structures\Heap.h"
#include "./Engine_Data Structures\GraphArc.h"
#include "./Engine_Data Structures\GraphNode.h"
#include "./Engine_Data Structures\Graph.h"

// Data Structures 부분 종료

// Engine System 부분

// File
#include "./Engine_System\FileStream.h"

// Assist
#include "./Engine_System\Gravity.h"

// Time
#include "./Engine_System\Timer.h"
#include "./Engine_System\CrudeTimer.h"
#include "./Engine_System\PrecisionTimer.h"

#include "./Engine_System\SystemFrame.h"
#include "./Engine_System\Information.h"
#include "./Engine_System\Camera.h"
#include "./Engine_System\Particle.h"
#include "./Engine_System\Snow.h"
#include "./Engine_System\Firework.h"
#include "./Engine_System\ParticleGun.h"
#include "./Engine_System\GetSmaller.h"
#include "./Engine_System\Dirt.h"
#include "./Engine_System\Exhaust.h"
#include "./Engine_System\Kindling.h"
#include "./Engine_System\DataParticle.h"
#include "./Engine_System\SpreadParticle.h"
#include "./Engine_System\Leaf.h"

#include "./Engine_System\Telegram.h"
#include "./Engine_System\EntityType.h"
#include "./Engine_System\BaseEntity.h"
#include "./Engine_System\State.h"
#include "./Engine_System\StateMachine.h"
#include "./Engine_System\MessageTypes.h"
#include "./Engine_System\EffectType.h"
#include "./Engine_System\EntityFunctionTemplates.h"
#include "./Engine_System\TextOwnedStates.h"
#include "./Engine_System\Text.h"

// Entity
#include "./Engine_System\DirectXEntity.h"
#include "./Engine_System\LineEntity.h"
#include "./Engine_System\BasicEntity.h"

#include "./Engine_System\Organ.h"
#include "./Engine_System\Body.h"
#include "./Engine_System\Attachment.h"

#include "./Engine_System\OrganEntity.h"
#include "./Engine_System\MovingEntity.h"
#include "./Engine_System\SteeringBehavior.h"
#include "./Engine_System\Vehicle.h"
#include "./Engine_System\PlanetEntityOwnedstates.h"
#include "./Engine_System\PlanetEntity.h"

// Effect
#include "./Engine_System\BaseEffect.h"
#include "./Engine_System\SpreadEffect.h"

// 어플리케이션
#include "./Engine_System\Wnd.h"
#include "./Engine_System\App.h"

// 파일
#include "./Engine_System\FileLoaderBase.h"
#include "./Engine_System\BaseParamLoader.h"
#include "./Engine_System\MapParamLoader.h"
#include "./Engine_System\SteeringParamLoader.h"
#include "./Engine_System\ScriptLoader.h"


// Engine System 부분 종료

//////////// Game_Factor

// Basic Composition
#include "./Game_Factor\Wall3D.h"
#include "./Game_Factor\Path.h"
#include "./Game_Factor\Obstacle.h"

// Contents
#include "./Game_Factor\Growth.h"
#include "./Game_Factor\ByteOwnedStates.h"
#include "./Game_Factor\Byte.h"
#include "./Game_Factor\BusOwnedStates.h"
#include "./Game_Factor\Bus.h"
#include "./Game_Factor\InfectionOwnedStates.h"
#include "./Game_Factor\Infection.h"
#include "./Game_Factor\WaveOwnedStates.h"
#include "./Game_Factor\Wave.h"
#include "./Game_Factor\DataBomb.h"
#include "./Game_Factor\BreakHeartOwnedStates.h"
#include "./Game_Factor\BreakHeart.h"

// Entity
#include "./Game_Factor\CellEntity.h"
#include "./Game_Factor\DataOwnedStates.h"
#include "./Game_Factor\Data.h"
#include "./Game_Factor\VirusOwnedStates.h"
#include "./Game_Factor\Virus.h"
#include "./Game_Factor\VacineOwnedStates.h"
#include "./Game_Factor\Vacine.h"
#include "./Game_Factor\SecretDataOwnedStates.h"
#include "./Game_Factor\SecretData.h"

// World
#include "./Game_Factor\World.h"

// UserInterface
#include "./Game_Factor\AbilityOwnedStates.h"
#include "./Game_Factor\Ability.h"
#include "./Game_Factor\GaugeOwnedStates.h"
#include "./Game_Factor\Gauge.h"
#include "./Game_Factor\MessageWindowOwnedStates.h"
#include "./Game_Factor\MessageWindow.h"
#include "./Game_Factor\CheckWIndowOwnedStates.h"
#include "./Game_Factor\CheckWindow.h"
#include "./Game_Factor\DialogWindowOwnedStates.h"
#include "./Game_Factor\DialogWindow.h"
#include "./Game_Factor\NumberOwnedStates.h"
#include "./Game_Factor\Number.h"
#include "./Game_Factor\NumberArray.h"
#include "./Game_Factor\TextOfGameOwnedStates.h"
#include "./Game_Factor\TextOfGame.h"
#include "./Game_Factor\GameMenuOwnedStates.h"
#include "./Game_Factor\GameMenu.h"
#include "./Game_Factor\GaugeOwnedStates.h"
#include "./Game_Factor\Gauge.h"
#include "./Game_Factor\Arrow.h"
#include "./Game_Factor\InputWindowOwnedStates.h"
#include "./Game_Factor\InputWindow.h"

// Controller
#include "./Game_Factor\Controller.h"

//////////// Game_Factor End

// Logic

// Section composition
#include "./Engine_Logic\LogoOwnedStates.h"
#include "./Engine_Logic\Logo.h"
#include "./Engine_Logic\CreditOwnedStates.h"
#include "./Engine_Logic\Credit.h"
#include "./Engine_Logic\MainMenuOwnedStates.h"
#include "./Engine_Logic\MainMenu.h"
#include "./Engine_Logic\LoadingOwnedStates.h"
#include "./Engine_Logic\Loading.h"
#include "./Engine_Logic\EndingOwnedStates.h"
#include "./Engine_Logic\Ending.h"
#include "./Engine_Logic\OST.h"
#include "./Engine_Logic\RankOwnedStates.h"
#include "./Engine_Logic\Rank.h"

// Event
#include "./Engine_Logic\EventMainStates.h"
#include "./Engine_Logic\EventSubStates.h"
#include "./Engine_Logic\Event.h"

// Section
#include "./Engine_Logic\SectionOwnedStates.h"
#include "./Engine_Logic\Section.h"

// Logic 종료

// 모든 관리자
#include "./Game_Factor\WorldManager.h"
#include "./Game_Factor\UIManager.h"
#include "./Engine_Math&Physics\MathManager.h"
#include "./Engine_Logic\SectionManager.h"
#include "./Engine_Logic\EventManager.h"
#include "./Engine_System\EntityManager.h"
#include "./Engine_System\EngineManager.h"
#include "./Engine_System\ParticleManager.h"
#include "./Engine_System\EffectManager.h"
#include "./Engine_System\CameraManager.h"
#include "./Engine_System\MouseManager.h"
#include "./Engine_System\CollisionManager.h"
#include "./Engine_System\MP3Manager.h"
#include "./Engine_System\WaveManager.h"
#include "./Engine_System\TimeManager.h"
#include "./Engine_System\MessageManager.h"

#endif