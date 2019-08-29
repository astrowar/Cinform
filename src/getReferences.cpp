

#include "PreCodeGenerate.hpp"
#include "NSource.hpp"
#include <cctype>
using namespace std;

namespace CInform
{
	using namespace Match;

	namespace CodeParser
	{
		std::list<MatchResultStr> getMatchs( ParserStore *pstore, string txt, string match );


		string get_instance_reference( ParserStore *pstore, string instname, PreCodeGenerate** error )
		{
			if (pstore->isInstance( instname ))
			{
				return pstore->getReference( instname );
			}

			return "";
		}



		bool is_adjetive_valid_for_reference( ParserStore *pstore, string adj_noum, string inst_ref )
		{
			return true;
		}

		list<string> get_adj_instance_reference( ParserStore *pstore, string adj_instname, PreCodeGenerate** error )
		{
			auto rss = getMatchs( pstore, adj_instname, "X Y" );
			for (auto rs : rss)
			{
				auto inst_name = rs.getResult( "Y" ).repr();
				auto inst_ref = get_instance_reference( pstore, inst_name, nullptr );
				if (inst_ref != "")
				{
					auto adj_noum = rs.getResult( "X" ).repr();
					bool is_adj_of = is_adjetive_valid_for_reference( pstore, adj_noum, inst_ref );
					if (is_adj_of)
					{
						return { inst_ref , adj_noum };
					}
				}
			}
			return {};
		}



		string get_kind_reference( ParserStore *pstore, string kindname, PreCodeGenerate** error )
		{

			kindname = removeArticle( pstore, kindname );

			if (kindname.find( ' ' ) == string::npos)
			{
				if (pstore->isImplicityVar( kindname )) return pstore->mangleg( kindname );
			}
			if (pstore->isKind( kindname ))
			{
				return pstore->getReference( kindname );
			}


			string kindref = isCompound( pstore, kindname, error );
			if (*error != nullptr) return "";
			if (kindref != "") 	return kindref;

			*error = new   PreCodeGenerateDependency( kindname );
			return "";

		}


		string get_verb_reference( ParserStore *pstore, string verb, PreCodeGenerate** error )
		{
			string vname = pstore->getVerbReference( verb );
			if (vname != "") return vname;

			//raise some error
			*error = new   PreCodeGenerateDependency( verb );
			return "";
		}


	}

}