
# include "Core.h"
# include "EmojiCodec.h"

WSI_BEGIN_CXX
WSI_BEGIN_NS(sys)

# define ADD(key, val) _map.insert(key, val)

EmojiConverter::EmojiConverter()
{
    // from softbank to unicode.
    ADD("\ue443", "\U0001f300");
    ADD("\ue43c", "\U0001f302");
    ADD("\ue44b", "\U0001f303");
    ADD("\ue04d", "\U0001f304");
    ADD("\ue146", "\U0001f306");
    ADD("\ue44a", "\U0001f307");
    ADD("\ue44c", "\U0001f308");
    ADD("\ue44b", "\U0001f309");
    ADD("\ue43e", "\U0001f30a");
    ADD("\ue04c", "\U0001f319");
    ADD("\ue04c", "\U0001f31b");
    ADD("\ue335", "\U0001f31f");
    ADD("\ue024", "\U0001f550");
    ADD("\ue025", "\U0001f551");
    ADD("\ue026", "\U0001f552");
    ADD("\ue027", "\U0001f553");
    ADD("\ue028", "\U0001f554");
    ADD("\ue029", "\U0001f555");
    ADD("\ue02a", "\U0001f556");
    ADD("\ue02b", "\U0001f557");
    ADD("\ue02c", "\U0001f558");
    ADD("\ue02d", "\U0001f559");
    ADD("\ue02e", "\U0001f55a");
    ADD("\ue02f", "\U0001f55b");
    ADD("\ue23f", "\U00012648");
    ADD("\ue240", "\U00012649");
    ADD("\ue241", "\U0001264a");
    ADD("\ue242", "\U0001264b");
    ADD("\ue243", "\U0001264c");
    ADD("\ue244", "\U0001264d");
    ADD("\ue245", "\U0001264e");
    ADD("\ue246", "\U0001264f");
    ADD("\ue247", "\U00012650");
    ADD("\ue248", "\U00012651");
    ADD("\ue249", "\U00012652");
    ADD("\ue24a", "\U00012653");
    ADD("\ue24b", "\U000126ce");
    ADD("\ue110", "\U0001f340");
    ADD("\ue304", "\U0001f337");
    ADD("\ue110", "\U0001f331");
    ADD("\ue118", "\U0001f341");
    ADD("\ue030", "\U0001f338");
    ADD("\ue032", "\U0001f339");
    ADD("\ue119", "\U0001f342");
    ADD("\ue447", "\U0001f343");
    ADD("\ue303", "\U0001f33a");
    ADD("\ue305", "\U0001f33b");
    ADD("\ue307", "\U0001f334");
    ADD("\ue308", "\U0001f335");
    ADD("\ue444", "\U0001f33e");
    ADD("\ue305", "\U0001f33c");
    ADD("\ue110", "\U0001f33f");
    ADD("\ue345", "\U0001f33e");
    ADD("\ue346", "\U0001f33a");
    ADD("\ue347", "\U0001f353");
    ADD("\ue348", "\U0001f349");
    ADD("\ue349", "\U0001f345");
    ADD("\ue34a", "\U0001f346");
    ADD("\ue345", "\U0001f34f");
    ADD("\ue419", "\U0001f440");
    ADD("\ue41b", "\U0001f442");
    ADD("\ue41a", "\U0001f443");
    ADD("\ue41c", "\U0001f444");
    ADD("\ue409", "\U0001f445");
    ADD("\ue31c", "\U0001f484");
    ADD("\ue31d", "\U0001f485");
    ADD("\ue31e", "\U0001f486");
    ADD("\ue31f", "\U0001f487");
    ADD("\ue320", "\U0001f488");
    ADD("\ue001", "\U0001f466");
    ADD("\ue002", "\U0001f467");
    ADD("\ue004", "\U0001f468");
    ADD("\ue005", "\U0001f469");
    ADD("\ue428", "\U0001f46b");
    ADD("\ue152", "\U0001f46e");
    ADD("\ue429", "\U0001f46f");
    ADD("\ue515", "\U0001f471");
    ADD("\ue516", "\U0001f472");
    ADD("\ue517", "\U0001f473");
    ADD("\ue518", "\U0001f474");
    ADD("\ue519", "\U0001f475");
    ADD("\ue51a", "\U0001f476");
    ADD("\ue51b", "\U0001f477");
    ADD("\ue51c", "\U0001f478");
    ADD("\ue11b", "\U0001f47b");
    ADD("\ue04e", "\U0001f47c");
    ADD("\ue10c", "\U0001f47d");
    ADD("\ue12b", "\U0001f47e");
    ADD("\ue11a", "\U0001f47f");
    ADD("\ue11c", "\U0001f480");
    ADD("\ue253", "\U0001f481");
    ADD("\ue51e", "\U0001f482");
    ADD("\ue51f", "\U0001f483");
    ADD("\ue52d", "\U0001f40d");
    ADD("\ue134", "\U0001f40e");
    ADD("\ue52e", "\U0001f414");
    ADD("\ue52f", "\U0001f417");
    ADD("\ue530", "\U0001f42b");
    ADD("\ue526", "\U0001f418");
    ADD("\ue527", "\U0001f428");
    ADD("\ue528", "\U0001f412");
    ADD("\ue529", "\U0001f411");
    ADD("\ue10a", "\U0001f419");
    ADD("\ue441", "\U0001f41a");
    ADD("\ue525", "\U0001f41b");
    ADD("\ue522", "\U0001f420");
    ADD("\ue019", "\U0001f421");
    ADD("\ue523", "\U0001f424");
    ADD("\ue523", "\U0001f425");
    ADD("\ue521", "\U0001f426");
    ADD("\ue523", "\U0001f423");
    ADD("\ue055", "\U0001f427");
    ADD("\ue052", "\U0001f429");
    ADD("\ue019", "\U0001f41f");
    ADD("\ue520", "\U0001f42c");
    ADD("\ue053", "\U0001f42d");
    ADD("\ue050", "\U0001f42f");
    ADD("\ue04f", "\U0001f431");
    ADD("\ue054", "\U0001f433");
    ADD("\ue01a", "\U0001f434");
    ADD("\ue109", "\U0001f435");
    ADD("\ue052", "\U0001f436");
    ADD("\ue10b", "\U0001f437");
    ADD("\ue051", "\U0001f43b");
    ADD("\ue524", "\U0001f439");
    ADD("\ue52a", "\U0001f43a");
    ADD("\ue52b", "\U0001f42e");
    ADD("\ue52c", "\U0001f430");
    ADD("\ue531", "\U0001f438");
    ADD("\ue536", "\U0001f43e");
    ADD("\ue10b", "\U0001f43d");
    ADD("\ue059", "\U0001f620");
    ADD("\ue403", "\U0001f629");
    ADD("\ue410", "\U0001f632");
    ADD("\ue058", "\U0001f61e");
    ADD("\ue406", "\U0001f635");
    ADD("\ue40f", "\U0001f630");
    ADD("\ue40e", "\U0001f612");
    ADD("\ue106", "\U0001f60d");
    ADD("\ue404", "\U0001f624");
    ADD("\ue105", "\U0001f61c");
    ADD("\ue409", "\U0001f61d");
    ADD("\ue056", "\U0001f60b");
    ADD("\ue418", "\U0001f618");
    ADD("\ue417", "\U0001f61a");
    ADD("\ue40c", "\U0001f637");
    ADD("\ue40d", "\U0001f633");
    ADD("\ue057", "\U0001f603");
    ADD("\ue404", "\U0001f601");
    ADD("\ue412", "\U0001f602");
    ADD("\ue056", "\U0001f60a");
    ADD("\ue057", "\U0001f63a");
    ADD("\ue415", "\U0001f604");
    ADD("\ue413", "\U0001f622");
    ADD("\ue411", "\U0001f62d");
    ADD("\ue40b", "\U0001f628");
    ADD("\ue406", "\U0001f623");
    ADD("\ue416", "\U0001f621");
    ADD("\ue40a", "\U0001f60c");
    ADD("\ue407", "\U0001f616");
    ADD("\ue403", "\U0001f614");
    ADD("\ue107", "\U0001f631");
    ADD("\ue408", "\U0001f62a");
    ADD("\ue402", "\U0001f60f");
    ADD("\ue108", "\U0001f613");
    ADD("\ue401", "\U0001f625");
    ADD("\ue406", "\U0001f62b");
    ADD("\ue405", "\U0001f609");
    ADD("\ue057", "\U0001f63a");
    ADD("\ue404", "\U0001f638");
    ADD("\ue412", "\U0001f639");
    ADD("\ue418", "\U0001f63d");
    ADD("\ue106", "\U0001f63b");
    ADD("\ue416", "\U0001f63e");
    ADD("\ue404", "\U0001f63c");
    ADD("\ue059", "\U0001f620");
    ADD("\ue403", "\U0001f629");
    ADD("\ue410", "\U0001f632");
    ADD("\ue058", "\U0001f61e");
    ADD("\ue406", "\U0001f635");
    ADD("\ue403", "\U0001f640");
    ADD("\ue423", "\U0001f645");
    ADD("\ue424", "\U0001f646");
    ADD("\ue426", "\U0001f647");
    ADD("\ue427", "\U0001f64c");
    ADD("\ue403", "\U0001f64d");
    ADD("\ue416", "\U0001f64e");
    ADD("\ue41d", "\U0001f64f");
    ADD("\ue036", "\U0001f3e0");
    ADD("\ue036", "\U0001f3e1");
    ADD("\ue038", "\U0001f3e2");
    ADD("\ue153", "\U0001f3e3");
    ADD("\ue155", "\U0001f3e5");
    ADD("\ue14d", "\U0001f3e6");
    ADD("\ue154", "\U0001f3e7");
    ADD("\ue158", "\U0001f3e8");
    ADD("\ue501", "\U0001f3e9");
    ADD("\ue156", "\U0001f3ea");
    ADD("\ue157", "\U0001f3eb");
    ADD("\ue037", "\U000126ea");
    ADD("\ue121", "\U000126f2");
    ADD("\ue504", "\U0001f3ec");
    ADD("\ue505", "\U0001f3ef");
    ADD("\ue506", "\U0001f3f0");
    ADD("\ue508", "\U0001f3ed");
    ADD("\ue202", "\U00012693");
    ADD("\ue30b", "\U0001f3ee");
    ADD("\ue03b", "\U0001f5fb");
    ADD("\ue509", "\U0001f5fc");
    ADD("\ue51d", "\U0001f5fd");
    ADD("\ue007", "\U0001f45e");
    ADD("\ue13e", "\U0001f460");
    ADD("\ue31a", "\U0001f461");
    ADD("\ue31b", "\U0001f462");
    ADD("\ue536", "\U0001f463");
    ADD("\ue006", "\U0001f455");
    ADD("\ue10e", "\U0001f451");
    ADD("\ue302", "\U0001f454");
    ADD("\ue318", "\U0001f452");
    ADD("\ue319", "\U0001f457");
    ADD("\ue321", "\U0001f458");
    ADD("\ue322", "\U0001f459");
    ADD("\ue006", "\U0001f45a");
    ADD("\ue149", "\U0001f4b1");
    ADD("\ue323", "\U0001f45c");
    ADD("\ue14a", "\U0001f4b9");
    ADD("\ue12f", "\U0001f4b0");
    ADD("\ue12f", "\U0001f4b2");
    ADD("\ue12f", "\U0001f4b5");
    ADD("\ue513", "\U0001f1e8");
    ADD("\ue50e", "\U0001f1e9");
    ADD("\ue511", "\U0001f1ea");
    ADD("\ue50d", "\U0001f1eb");
    ADD("\ue510", "\U0001f1ec");
    ADD("\ue50f", "\U0001f1ee");
    ADD("\ue50b", "\U0001f1ef");
    ADD("\ue514", "\U0001f1f0");
    ADD("\ue512", "\U0001f1f7");
    ADD("\ue50c", "\U0001f1fa");
    ADD("\ue11d", "\U0001f525");
    ADD("\ue116", "\U0001f528");
    ADD("\ue113", "\U0001f52b");
    ADD("\ue23e", "\U0001f52f");
    ADD("\ue209", "\U0001f530");
    ADD("\ue031", "\U0001f531");
    ADD("\ue13b", "\U0001f489");
    ADD("\ue30f", "\U0001f48a");
    ADD("\ue532", "\U0001f170");
    ADD("\ue533", "\U0001f171");
    ADD("\ue534", "\U0001f18e");
    ADD("\ue535", "\U0001f17e");
    ADD("\ue314", "\U0001f380");
    ADD("\ue112", "\U0001f381");
    ADD("\ue34b", "\U0001f382");
    ADD("\ue033", "\U0001f384");
    ADD("\ue448", "\U0001f385");
    ADD("\ue143", "\U0001f38c");
    ADD("\ue117", "\U0001f386");
    ADD("\ue310", "\U0001f388");
    ADD("\ue312", "\U0001f389");
    ADD("\ue436", "\U0001f38d");
    ADD("\ue438", "\U0001f38e");
    ADD("\ue439", "\U0001f393");
    ADD("\ue43a", "\U0001f392");
    ADD("\ue43b", "\U0001f38f");
    ADD("\ue440", "\U0001f387");
    ADD("\ue442", "\U0001f390");
    ADD("\ue445", "\U0001f383");
    ADD("\ue446", "\U0001f391");
    ADD("\ue009", "\U0001260e");
    ADD("\ue009", "\U0001f4de");
    ADD("\ue00a", "\U0001f4f1");
    ADD("\ue104", "\U0001f4f2");
    ADD("\ue301", "\U0001f4dd");
    ADD("\ue00b", "\U0001f4e0");
    ADD("\ue103", "\U00012709");
    ADD("\ue103", "\U0001f4e8");
    ADD("\ue103", "\U0001f4ea");
    ADD("\ue101", "\U0001f4eb");
    ADD("\ue101", "\U0001f4ee");
    ADD("\ue102", "\U0001f4f0");
    ADD("\ue142", "\U0001f4e2");
    ADD("\ue317", "\U0001f4e3");
    ADD("\ue14b", "\U0001f4e1");
    ADD("\ue112", "\U0001f4e6");
    ADD("\ue103", "\U0001f4e7");
    ADD("\ue11f", "\U0001f4ba");
    ADD("\ue00c", "\U0001f4bb");
    ADD("\ue301", "\U0001270f");
    ADD("\ue11e", "\U0001f4bc");
    ADD("\ue316", "\U0001f4bd");
    ADD("\ue316", "\U0001f4be");
    ADD("\ue126", "\U0001f4bf");
    ADD("\ue127", "\U0001f4c0");
    ADD("\ue313", "\U00012702");
    ADD("\ue301", "\U0001f4c3");
    ADD("\ue301", "\U0001f4c4");
    ADD("\ue148", "\U0001f4d6");
    ADD("\ue14a", "\U0001f4ca");
    ADD("\ue016", "\U000126be");
    ADD("\ue014", "\U000126f3");
    ADD("\ue015", "\U0001f3be");
    ADD("\ue013", "\U0001f3bf");
    ADD("\ue42a", "\U0001f3c0");
    ADD("\ue132", "\U0001f3c1");
    ADD("\ue115", "\U0001f3c3");
    ADD("\ue017", "\U0001f3c4");
    ADD("\ue131", "\U0001f3c6");
    ADD("\ue42b", "\U0001f3c8");
    ADD("\ue42d", "\U0001f3ca");
    ADD("\ue01e", "\U0001f683");
    ADD("\ue434", "\U0001f687");
    ADD("\ue435", "\U0001f684");
    ADD("\ue01f", "\U0001f685");
    ADD("\ue01b", "\U0001f697");
    ADD("\ue42e", "\U0001f699");
    ADD("\ue159", "\U0001f68c");
    ADD("\ue150", "\U0001f68f");
    ADD("\ue202", "\U0001f6a2");
    ADD("\ue01d", "\U00012708");
    ADD("\ue01c", "\U000126f5");
    ADD("\ue039", "\U0001f689");
    ADD("\ue10d", "\U0001f680");
    ADD("\ue135", "\U0001f6a4");
    ADD("\ue15a", "\U0001f695");
    ADD("\ue42f", "\U0001f69a");
    ADD("\ue430", "\U0001f692");
    ADD("\ue431", "\U0001f691");
    ADD("\ue432", "\U0001f693");
    ADD("\ue03a", "\U000126fd");
    ADD("\ue14f", "\U0001f17f");
    ADD("\ue14e", "\U0001f6a5");
    ADD("\ue137", "\U0001f6a7");
    ADD("\ue432", "\U0001f6a8");
    ADD("\ue123", "\U00012668");
    ADD("\ue122", "\U000126fa");
    ADD("\ue124", "\U0001f3a1");
    ADD("\ue433", "\U0001f3a2");
    ADD("\ue019", "\U0001f3a3");
    ADD("\ue03c", "\U0001f3a4");
    ADD("\ue03d", "\U0001f3a5");
    ADD("\ue507", "\U0001f3a6");
    ADD("\ue30a", "\U0001f3a7");
    ADD("\ue502", "\U0001f3a8");
    ADD("\ue503", "\U0001f3a9");
    ADD("\ue125", "\U0001f3ab");
    ADD("\ue324", "\U0001f3ac");
    ADD("\ue503", "\U0001f3ad");
    ADD("\ue12d", "\U0001f004");
    ADD("\ue130", "\U0001f3af");
    ADD("\ue133", "\U0001f3b0");
    ADD("\ue42c", "\U0001f3b1");
    ADD("\ue03e", "\U0001f3b5");
    ADD("\ue326", "\U0001f3b6");
    ADD("\ue040", "\U0001f3b7");
    ADD("\ue041", "\U0001f3b8");
    ADD("\ue042", "\U0001f3ba");
    ADD("\ue326", "\U0001f3bc");
    ADD("\ue12c", "\U0001303d");
    ADD("\ue008", "\U0001f4f7");
    ADD("\ue03d", "\U0001f4f9");
    ADD("\ue12a", "\U0001f4fa");
    ADD("\ue128", "\U0001f4fb");
    ADD("\ue129", "\U0001f4fc");
    ADD("\ue003", "\U0001f48b");
    ADD("\ue034", "\U0001f48d");
    ADD("\ue035", "\U0001f48e");
    ADD("\ue111", "\U0001f48f");
    ADD("\ue306", "\U0001f490");
    ADD("\ue425", "\U0001f491");
    ADD("\ue43d", "\U0001f492");
    ADD("\ue207", "\U0001f51e");
    ADD("\ue24e", "\U000100a9");
    ADD("\ue24f", "\U000100ae");
    ADD("\ue537", "\U00012122");
    ADD("\ue20b", "\U0001f4f6");
    ADD("\ue250", "\U0001f4f3");
    ADD("\ue251", "\U0001f4f4");
    ADD("\ue120", "\U0001f354");
    ADD("\ue342", "\U0001f359");
    ADD("\ue046", "\U0001f370");
    ADD("\ue340", "\U0001f35c");
    ADD("\ue339", "\U0001f35e");
    ADD("\ue147", "\U0001f373");
    ADD("\ue33a", "\U0001f366");
    ADD("\ue33b", "\U0001f35f");
    ADD("\ue33c", "\U0001f361");
    ADD("\ue33d", "\U0001f358");
    ADD("\ue33e", "\U0001f35a");
    ADD("\ue33f", "\U0001f35d");
    ADD("\ue341", "\U0001f35b");
    ADD("\ue343", "\U0001f362");
    ADD("\ue344", "\U0001f363");
    ADD("\ue34c", "\U0001f371");
    ADD("\ue34d", "\U0001f372");
    ADD("\ue43f", "\U0001f367");
    ADD("\ue043", "\U0001f374");
    ADD("\ue044", "\U0001f378");
    ADD("\ue047", "\U0001f37a");
    ADD("\ue338", "\U0001f375");
    ADD("\ue30b", "\U0001f376");
    ADD("\ue044", "\U0001f377");
    ADD("\ue30c", "\U0001f37b");
    ADD("\ue044", "\U0001f379");
    ADD("\ue236", "\U00012197");
    ADD("\ue238", "\U00012198");
    ADD("\ue237", "\U00012196");
    ADD("\ue239", "\U00012199");
    ADD("\ue236", "\U00012934");
    ADD("\ue238", "\U00012935");
    ADD("\ue232", "\U00012b06");
    ADD("\ue233", "\U00012b07");
    ADD("\ue234", "\U000127a1");
    ADD("\ue235", "\U00012b05");
    ADD("\ue23a", "\U000125b6");
    ADD("\ue23b", "\U000125c0");
    ADD("\ue23c", "\U000123e9");
    ADD("\ue23d", "\U000123ea");
    ADD("\ue332", "\U00012b55");
    ADD("\ue333", "\U0001274c");
    ADD("\ue211", "\U000127bf");
    ADD("\ue327", "\U0001f493");
    ADD("\ue023", "\U0001f494");
    ADD("\ue327", "\U0001f496");
    ADD("\ue328", "\U0001f497");
    ADD("\ue329", "\U0001f498");
    ADD("\ue32a", "\U0001f499");
    ADD("\ue32b", "\U0001f49a");
    ADD("\ue32c", "\U0001f49b");
    ADD("\ue32d", "\U0001f49c");
    ADD("\ue437", "\U0001f49d");
    ADD("\ue204", "\U0001f49f");
    ADD("\ue20c", "\U00012665");
    ADD("\ue20e", "\U00012660");
    ADD("\ue20d", "\U00012666");
    ADD("\ue20f", "\U00012663");
    ADD("\ue30e", "\U0001f6ac");
    ADD("\ue208", "\U0001f6ad");
    ADD("\ue20a", "\U0001267f");
    ADD("\ue252", "\U000126a0");
    ADD("\ue137", "\U000126d4");
    ADD("\ue136", "\U0001f6b2");
    ADD("\ue201", "\U0001f6b6");
    ADD("\ue138", "\U0001f6b9");
    ADD("\ue139", "\U0001f6ba");
    ADD("\ue13f", "\U0001f6c0");
    ADD("\ue151", "\U0001f6bb");
    ADD("\ue140", "\U0001f6bd");
    ADD("\ue309", "\U0001f6be");
    ADD("\ue13a", "\U0001f6bc");
    ADD("\ue214", "\U0001f192");
    ADD("\ue229", "\U0001f194");
    ADD("\ue212", "\U0001f195");
    ADD("\ue24d", "\U0001f197");
    ADD("\ue213", "\U0001f199");
    ADD("\ue12e", "\U0001f19a");
    ADD("\ue203", "\U0001f201");
    ADD("\ue228", "\U0001f202");
    ADD("\ue22b", "\U0001f233");
    ADD("\ue22a", "\U0001f235");
    ADD("\ue215", "\U0001f236");
    ADD("\ue216", "\U0001f21a");
    ADD("\ue217", "\U0001f237");
    ADD("\ue218", "\U0001f238");
    ADD("\ue227", "\U0001f239");
    ADD("\ue22c", "\U0001f22f");
    ADD("\ue22d", "\U0001f23a");
    ADD("\ue315", "\U00013299");
    ADD("\ue30d", "\U00013297");
    ADD("\ue226", "\U0001f250");
    ADD("\ue333", "\U00012716");
    ADD("\ue10f", "\U0001f4a1");
    ADD("\ue311", "\U0001f4a3");
    ADD("\ue331", "\U0001f239");
    ADD("\ue330", "\U0001f4a8");
    ADD("\ue13c", "\U0001f4a4");
    ADD("\ue05a", "\U0001f4a9");
    ADD("\ue14c", "\U0001f4aa");
    ADD("\ue407", "\U0001f4ab");
    ADD("\ue205", "\U00012734");
    ADD("\ue219", "\U000126ab");
    ADD("\ue141", "\U0001f50a");
    ADD("\ue114", "\U0001f50d");
    ADD("\ue144", "\U0001f512");
    ADD("\ue145", "\U0001f513");
    ADD("\ue03f", "\U0001f511");
    ADD("\ue325", "\U0001f514");
    ADD("\ue235", "\U0001f519");
    ADD("\ue24c", "\U0001f51d");
    ADD("\ue010", "\U0001270a");
    ADD("\ue00d", "\U0001f44a");
    ADD("\ue00e", "\U0001f44d");
    ADD("\ue22e", "\U0001f446");
    ADD("\ue22f", "\U0001f447");
    ADD("\ue230", "\U0001f448");
    ADD("\ue231", "\U0001f449");
    ADD("\ue41e", "\U0001f44b");
    ADD("\ue41f", "\U0001f44f");
    ADD("\ue420", "\U0001f44c");
    ADD("\ue421", "\U0001f44e");
    ADD("\ue422", "\U0001f450");
}

EmojiConverter& EmojiConverter::getInstance()
{
    static EmojiConverter __gs_emoji;
    static EmojiVersion __gs_version;
    
    return __gs_emoji;
}

core::string const& EmojiConverter::unicode(core::string const& str) const
{
    if (EmojiVersion::VERSION_SOFTBANK)
        return str;
    
    map_type::left_map_type::const_iterator found = _map.left_map.find(str);
    if (found == _map.left_map.end())
        return core::null_string;
    
    return found->second;
}

WSI_END_NS
WSI_END_CXX
