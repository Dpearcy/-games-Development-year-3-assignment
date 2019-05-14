
#include "CParzivalLevel.h"

namespace gen
{

	CParzivalLevel::CParzivalLevel(CEntityManager*  ENtityManager, CTeamManager* TeamManager)
	{
		m_EntityManager = ENtityManager;
		m_TeamManager = TeamManager;
		////file
		m_CurrentSection = none;

		//// template 
		m_TemplateType = "";
		m_TamplateName = "";
		m_TemplateMesh = "";
		m_RenderType = "";
		m_MaxHP = 0;
		m_ShellDamage = 0;
		m_MaxShells = 0;
		m_Acceleration = 0.0f;
		m_MaxSpeed = 0.0f;
		m_Turnspeed = 0.0f;
		m_TurrentTurnSpeed = 0.0f;

		//// entity 
		m_EntityType = "";
		m_EntityName = "";
		m_postion = CVector3::kOrigin;
		m_rototion = CVector3::kOrigin;
		m_ScaleOfModel = CVector3(1.0f, 1.0f, 1.0f);

	}
	void CParzivalLevel::StartElement(const string& elementName, SAttribute* attrs)//// This is call at start of the element.
	{
		if (elementName == "Templates")
		{
			m_CurrentSection = templates;
		}
		else if (elementName == "Entities")
		{
			m_CurrentSection = Entites;
		}
		else if (elementName == "Patrol")
		{
			m_CurrentSection = Patrol;
		}
		else if (elementName == "Formation")
		{
			m_CurrentSection = Formation;
		}
		switch (m_CurrentSection)
		{
		case templates:
			TemplateStartElement(elementName, attrs);
			break;
		case Entites:
			EntitlesStartElement(elementName, attrs);
			break;
		case Patrol:
			PatrolStartElement(elementName, attrs);
			break;
		case Formation:
			FormationStartElement(elementName, attrs);
			break;
		}
	}
	void CParzivalLevel::EndElement(const string& elementName)//// This is called at the end of the element.
	{
		if (elementName == "Templates" || elementName == "Entities")
		{
			m_CurrentSection = none;
		}
		switch (m_CurrentSection)
		{
		case templates:
			TemplateEndElement(elementName);
			break;
		case Entites:
			EntitlesEndElement(elementName);
			break;
		case Patrol:
			PatrolEndElement(elementName);
			break;
		case Formation:
			FormationEndElement(elementName);
			break;

		}
	}

	void CParzivalLevel::TemplateStartElement(const string& elementName, SAttribute* attrs) //// used  at start of element for the templates part of the file.
	{
		if (elementName == "EntityTemplate")
		{
			m_TemplateType = GetAttribute(attrs, "Type");
			m_TamplateName = GetAttribute(attrs, "Name");
			m_TemplateMesh = GetAttribute(attrs, "Mesh");
			m_RenderType = GetAttribute(attrs, "RanderType");
			m_EntityManager->CreateTemplate(m_TemplateType, m_TamplateName, m_TemplateMesh);
		}
		if (m_TemplateType == "Tank")
		{
			m_MaxHP = GetIntAttribute(attrs, "MaxHP");
			m_ShellDamage = GetIntAttribute(attrs, "ShellDamage");
			m_MaxShells = GetIntAttribute(attrs, "MaxShells");
			m_Acceleration = GetFloatAttribute(attrs,"Acceleration");
			m_MaxSpeed = GetFloatAttribute(attrs, "MaxSpeed");
			m_Turnspeed = GetFloatAttribute(attrs, "TurnSpeed");
			m_TurrentTurnSpeed = GetFloatAttribute(attrs, "TurrentTurnSpeed");
			m_RenderType = GetAttribute(attrs, "RanderType");
		}
	}
	void CParzivalLevel::TemplateEndElement(const string& elementName)//// used at end of element for the templates part of the file.
	{
		if (elementName == "EntityTemplate")
		{
			CreateEntityTemplate();
		}
	}
	void CParzivalLevel::EntitlesStartElement(const string& elementName, SAttribute* attrs)//// used  at start of element for the entitles part of the file.
	{
		if (elementName == "Team")
		{
			m_TeamName = GetAttribute(attrs, "Name");
			m_teamColor = GetAttribute(attrs, "TeamColor");
		}
		else if (elementName == "Entity")
		{
			m_EntityType = GetAttribute(attrs, "Type");
			m_EntityName = GetAttribute(attrs, "Name");
			m_postion = CVector3::kOrigin;
			m_rototion = CVector3::kZero;
			m_ScaleOfModel = CVector3(1.0f, 1.0f, 1.0f);
		}
		
		if (elementName == "Position")
		{
			m_postion.x = GetFloatAttribute(attrs, "X");
			m_postion.y = GetFloatAttribute(attrs, "Y");
			m_postion.z = GetFloatAttribute(attrs, "Z");
		}
		else if (elementName == "Rotation")
		{
			m_rototion.x = ToRadians(GetFloatAttribute(attrs, "X"));
			m_rototion.y = ToRadians(GetFloatAttribute(attrs, "Y"));
			m_rototion.z = ToRadians(GetFloatAttribute(attrs, "Z"));
		}
		else if (elementName == "Scale")
		{
			m_ScaleOfModel.x = (GetFloatAttribute(attrs, "X"));
			m_ScaleOfModel.y = (GetFloatAttribute(attrs, "Y"));
			m_ScaleOfModel.z = (GetFloatAttribute(attrs, "Z"));
		}
		else if (elementName == "Randomize")
		{
			float randomX = GetFloatAttribute(attrs, "X");
			float randomY = GetFloatAttribute(attrs, "Y");
			float randomZ = GetFloatAttribute(attrs, "Z");
			m_postion.x += Random(-randomX, randomX);
			m_postion.y += Random(-randomY, randomY);
			m_postion.z += Random(-randomZ, randomZ);
		}
	}
	void CParzivalLevel::EntitlesEndElement(const string& elementName)//// used  at end of element for the entitles part of the file.
	{
		if (elementName == "Team")
		{
			m_TeamName = "";
			m_teamColor = "";
		}
		else if (elementName == "Entity")
		{
			CreateEntity();
		}
	}
	void CParzivalLevel::PatrolStartElement(const string& elementName, SAttribute* attrs)
	{
		if (elementName == "Position")
		{
			CVector3 pos;
			pos.x = GetFloatAttribute(attrs, "X");
			pos.y = GetFloatAttribute(attrs, "Y");
			pos.z = GetFloatAttribute(attrs, "Z");
			m_PatrolPosition.push_back(pos);
		}

	}
	void CParzivalLevel::PatrolEndElement(const string& elementName)
	{
		if(elementName == "Patrol")
		{ 
				 m_CurrentSection = Entites;

		}

	}
	void CParzivalLevel::FormationStartElement(const string& elementName, SAttribute* attrs)
	{
		if (elementName == "PositionOfLeader")
		{
			m_PostionOfLeader.x = GetFloatAttribute(attrs, "X");
			m_PostionOfLeader.y = GetFloatAttribute(attrs, "Y");
			m_PostionOfLeader.z = GetFloatAttribute(attrs, "Z");
		}
		if (elementName == "PositionOfsceond")
		{
			m_PositonOfSecond.x = GetFloatAttribute(attrs, "X");
			m_PositonOfSecond.y = GetFloatAttribute(attrs, "Y");
			m_PositonOfSecond.z = GetFloatAttribute(attrs, "Z");
		}
		if (elementName == "PositionOfthrid")
		{
			m_PositonOfThird.x = GetFloatAttribute(attrs, "X");
			m_PositonOfThird.y = GetFloatAttribute(attrs, "Y");
			m_PositonOfThird.z = GetFloatAttribute(attrs, "Z");
		}
		if (elementName == "PositionOffourth")
		{
			m_PositionOfFourth.x = GetFloatAttribute(attrs, "X");
			m_PositionOfFourth.y = GetFloatAttribute(attrs, "Y");
			m_PositionOfFourth.z = GetFloatAttribute(attrs, "Z");
		}
		if (elementName == "Position")
		{
			CVector3 pos;
			pos.x = GetFloatAttribute(attrs, "X");
			pos.y = GetFloatAttribute(attrs, "Y");
			pos.z = GetFloatAttribute(attrs, "Z");
			m_OtherPostions.push_back(pos);
		}
		if (elementName == "PartolPosition")
		{
			CVector3 pos;
			pos.x = GetFloatAttribute(attrs, "X");
			pos.y = GetFloatAttribute(attrs, "Y");
			pos.z = GetFloatAttribute(attrs, "Z");
			m_PatrolPath.push_back(pos);
		}
	}

	void CParzivalLevel::FormationEndElement(const string& elementName)
	{
		if (elementName == "Formation")
		{
			StoreFormation();
			m_OtherPostions.clear();
			m_PatrolPath.clear();
			m_CurrentSection = Entites;
		}
	}
	void CParzivalLevel::StoreFormation()
	{
		m_TeamManager->StoreFormation(m_teamFormation, m_TeamName, m_PostionOfLeader,
			m_PositonOfSecond, m_PositonOfThird, m_PositionOfFourth, m_OtherPostions, m_PatrolPath);
	}
	void CParzivalLevel::CreateEntityTemplate()
	{
		if (m_TemplateType == "Tank")
		{
			m_EntityManager->CreateTankTemplate(m_TemplateType, m_TamplateName, m_TemplateMesh, m_MaxSpeed, m_Acceleration,
				m_Turnspeed, m_TurrentTurnSpeed, m_MaxHP, m_ShellDamage, m_MaxShells);
		}
		else
		{
			m_EntityManager->CreateTemplate(m_TemplateType, m_TamplateName, m_TemplateMesh);
		}
		
	}
	void CParzivalLevel::CreateEntity()
	{
		string TemplateType = m_EntityManager->GetTemplate(m_EntityType)->GetType();

		if (TemplateType == "Tank")
		{
			m_EntityManager->CreateTank(m_EntityType, m_TeamName, m_teamColor,
			m_PatrolPosition,m_EntityName, m_postion, m_rototion, m_ScaleOfModel);
			m_PatrolPosition.clear();
		}
		else
		{
			m_EntityManager->CreateEntity(m_EntityType, m_EntityName, m_postion,
			m_rototion, m_ScaleOfModel);
		}
	}

}