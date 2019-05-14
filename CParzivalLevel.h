#ifndef Gen_C_Parzival_LEVEL_H_INCLUDED
#define Gen_C_Parzival_LEVEL_H_INCLUDED

//// functions got from LN in the  CParseLevel.cpp  made on  30-Jul-2005 14:40:00
#include "Defines.h"
#include "CVector3.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "CParzivalXML.h"

namespace gen
{

	class CParzivalLevel : public CParzivalXML
	{
	private:
		CEntityManager* m_EntityManager;
		CTeamManager * m_TeamManager;
		//// the types of files that be passed into the here.
		enum EFileSection
		{
			none,
			templates,
			Entites,
			Patrol,
			Formation,
		};

		EFileSection m_CurrentSection; //// the current file state.

	    //// current Template state.
		string m_TemplateType;
		string m_TamplateName;
		string m_TemplateMesh;
		string m_RenderType;
		TUInt32 m_MaxHP;
		TUInt32 m_ShellDamage;
		TUInt32 m_MaxShells;
		TFloat32 m_Acceleration;
		TFloat32  m_MaxSpeed;
		TFloat32  m_Turnspeed;
		TFloat32  m_TurrentTurnSpeed;

		//// Current Formation
		CVector3 m_PostionOfLeader;
		CVector3 m_PositonOfSecond;
		CVector3 m_PositonOfThird;
		CVector3 m_PositionOfFourth;
		vector<CVector3> m_OtherPostions;
		vector<CVector3> m_PatrolPath;

		//// current entity state.
		CEntity* m_Entity;
		string m_EntityType;
		string m_EntityName;
		string m_TeamName;
		string m_teamColor;
		string m_teamFormation;
		CVector3 m_postion;
		CVector3 m_rototion;
		CVector3 m_ScaleOfModel;
		vector<CVector3> m_PatrolPosition;


		void StartElement(const string& elementName, SAttribute* attrs);//// This is call at start of the element.
		void EndElement(const string& elementName);//// This is called at the end of the element.

		void TemplateStartElement(const string& elementName, SAttribute* attrs); //// used  at start of element for the templates part of the file.
		void TemplateEndElement(const string& elementName);//// used at end of element for the templates part of the file.
		void EntitlesStartElement(const string& elementName, SAttribute* attrs);//// used  at start of element for the entitles part of the file.
		void EntitlesEndElement(const string& elementName);//// used  at end of element for the entitles part of the file.
		void PatrolStartElement(const string& elementName, SAttribute* attrs);//// used at the start of the patrol part of the file
		void PatrolEndElement(const string& elementName);//// used at the end of the element for the patrol part of the file
		void FormationStartElement(const string& elementName, SAttribute* attrs);//// used at the start of the formation part of the file
		void FormationEndElement(const string& elementName);//// used at the end of the element for the formation part of the file
		void CreateEntityTemplate();/// makes the templates for the entitys.
		void CreateEntity(); //// makes the entitys.
		void StoreFormation();//// this gives the data to the teamManager.

	public:
		CParzivalLevel(CEntityManager*  ENtityManager,CTeamManager* TeamManager);
	};
}
#endif // !Gen_C_Parzival_LEVEL_H_INCLUDED