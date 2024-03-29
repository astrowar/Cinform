
#include "CodeParser.hpp"
 
#include <map>
#include <list>

using namespace std;

namespace CInform
{
	namespace CodeParser
	{
		PreCodeGenerate * processSourcePreCodeGenerate( ParserStore * pstore, CInform::Match::TMatch & ematch, SParagraph * code_line, ParserEntryGroup * parserentries );
		map<string, list<PreCodeGenerate*> > processSource(ParserStore *pstore, SParagraph* code, ParserEntryGroup* parserentries );

		std::list<std::string> emiteInter( ParserStore *pstore, SParagraph* code)
		{
			CInform::GrammarContext* gtx = pstore->grammar();

			list<ParserEntry > parserentries_list;
			parserentries_list.emplace_back( "phaseDeclVerb", getPMatchExpended( " to X", gtx ) );
			//parserentries_list.emplace_back( "phaseDeclVerb2", getPMatchExpended( " to X Y  ", gtx ) );

			if (true)
			{

				parserentries_list.emplace_back( "phaseInsteadwhen", getPMatchExpended( "Instead of X when Y", gtx ) );
				parserentries_list.emplace_back( "phaseInstead", getPMatchExpended( "Instead of X , Y", gtx ) );
				parserentries_list.emplace_back( "phaseInstead", getPMatchExpended( "Instead of X : Y", gtx ) );
				parserentries_list.emplace_back( "phaseInstead", getPMatchExpended( "Instead of X :", gtx ) );


				parserentries_list.emplace_back( "phaseDeclDecide", getPMatchExpended( " to decide if X is Y ", gtx ) );
				parserentries_list.emplace_back( "phaseDeclDecide", getPMatchExpended( " X is/are Y if Z", gtx ) );
				parserentries_list.emplace_back( "phaseDeclwhich", getPMatchExpended( " to decide which/what X is Y ", gtx ) );

				//parserentries_list.emplace_back( "phaseDeclVerb", getPMatchExpended( " to X which  Y ", gtx ) );
		 

				parserentries_list.emplace_back( "assertKind", getPMatchExpended( " X is a/an kind ", gtx ) );
				parserentries_list.emplace_back( "assertKindValue", getPMatchExpended( " X is a/an kind of value", gtx ) );
				parserentries_list.emplace_back( "assertKindOf", getPMatchExpended( " X is/are a/an kind of   Y ", gtx ) );
				parserentries_list.emplace_back( "assertInstance", getPMatchExpended( " X is/are a/an   Y   ", gtx ) );
 
				parserentries_list.emplace_back( "assertAdjetive", getPMatchExpended( " X is/are Y ", gtx ) );

				//A thing can be fixed in place or portable
				parserentries_list.emplace_back( "assertAdjetiveEnum", getPMatchExpended( " X can be Y ", gtx ) );

				//A dead end has some text called the river sound.
				parserentries_list.emplace_back( "assertMemberVariable", getPMatchExpended( " X has ?a/an/some Y called Z ", gtx ) );

				//A object  is usually portable
				parserentries_list.emplace_back( "assertUsually", getPMatchExpended( " X is/are usually Y ", gtx ) );


				parserentries_list.emplace_back( "assertVariable", getPMatchExpended( " X is/are ?a/an/some  Y that varies ", gtx ) );
				 
			}

			ParserEntryGroup*  parserentries = new ParserEntryGroup(parserentries_list);

			map<string, list<PreCodeGenerate*> >  itList = processSource( pstore,code, parserentries );

			list<string> asm_out;
			for (auto &kv : itList)
			{
				asm_out.push_back(kv.first + ":");
				auto ls = emiteAsm(kv.second);
				asm_out.insert(asm_out.end(), ls.begin(), ls.end());
			}
			return asm_out;
		}
	

		bool testsForSelector( ParserStore *pstore );
		 


		std::list<std::string> emiteInter(   SParagraph* code )
		{
			auto gtx = new GrammarContextEnglish();
			ParserStore *pstore = new ParserStore( gtx );

			//fill pstore
			
			pstore->add( new CInform::Kind( SReference("kind"),   "kind" ));
			pstore->add( new CInform::Kind( SReference("value"), SReference( "kind" ), "value" ) );
			pstore->add( new CInform::Kind( SReference("number"), SReference( "value" ), "number" ) );
			pstore->add( new CInform::Kind( SReference("action"), SReference( "kind" ), "action" ) );
			pstore->add( new CInform::Kind( SReference("text"), SReference( "kind" ), "text" ) );
			

			testsForSelector( pstore );
			return emiteInter( pstore , code );
		}
	}
}
