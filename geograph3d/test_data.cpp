#include "test_data.hpp"
#include "jute.hpp"

using namespace GeoGraph3D;

#define FLOOR_HEIGHT 0.03f;

//#define DEBUG_TEST_TRANSITIONS

void FillGraphExample01(Graph* graph) {
    if(graph != NULL) {
        Roads roads;
        
        std::string jsonRoads = "{\"0\":[[{\"lat\":55.776253774269,\"lng\":37.655278220773},{\"lat\":55.776278853811,\"lng\":37.655394896865}],[{\"lat\":55.77626037415,\"lng\":37.655214853585},{\"lat\":55.776306761854,\"lng\":37.655435800552}],[{\"lat\":55.776328258577,\"lng\":37.655305378139},{\"lat\":55.776262636966,\"lng\":37.655350640416}],[{\"lat\":55.77670897488,\"lng\":37.654993906617},{\"lat\":55.776295447785,\"lng\":37.655281573534}],[{\"lat\":55.776296202057,\"lng\":37.655261792243},{\"lat\":55.776310721778,\"lng\":37.655330523849}],[{\"lat\":55.776309213236,\"lng\":37.655254416168},{\"lat\":55.77632392152,\"lng\":37.655321471393}],[{\"lat\":55.776317321649,\"lng\":37.655205465853},{\"lat\":55.776332218498,\"lng\":37.655271850526}],[{\"lat\":55.776632228505,\"lng\":37.655327171087},{\"lat\":55.776577544264,\"lng\":37.655072361231}],[{\"lat\":55.776617708904,\"lng\":37.655151486397},{\"lat\":55.77659413811,\"lng\":37.655168250203}],[{\"lat\":55.776572264402,\"lng\":37.654974795878},{\"lat\":55.776596966606,\"lng\":37.65508711338}],[{\"lat\":55.776581692726,\"lng\":37.654983848333},{\"lat\":55.776568870204,\"lng\":37.65499189496}],[{\"lat\":55.776642788212,\"lng\":37.654953338206},{\"lat\":55.776676918673,\"lng\":37.655109241605}],[{\"lat\":55.776700866548,\"lng\":37.654918134212},{\"lat\":55.776639582587,\"lng\":37.654960714281}],[{\"lat\":55.776733488432,\"lng\":37.655066996813},{\"lat\":55.776672015957,\"lng\":37.655109576881}],[{\"lat\":55.776689364027,\"lng\":37.654993571341},{\"lat\":55.776702563641,\"lng\":37.655004970729}]],\"2\":[[{\"lat\":55.775980538208,\"lng\":37.655193731189},{\"lat\":55.776082742673,\"lng\":37.655125334859},{\"lat\":55.776097451043,\"lng\":37.655194401741}],[{\"lat\":55.776083496949,\"lng\":37.655710726976},{\"lat\":55.776194375288,\"lng\":37.655634284019},{\"lat\":55.776178535545,\"lng\":37.655559852719}],[{\"lat\":55.776171747081,\"lng\":37.655123323202},{\"lat\":55.77675668201,\"lng\":37.654733397067},{\"lat\":55.776784778277,\"lng\":37.654754854739},{\"lat\":55.776882077943,\"lng\":37.654687799513},{\"lat\":55.776870952605,\"lng\":37.65463784337},{\"lat\":55.776819097179,\"lng\":37.654674053192}],[{\"lat\":55.776241140207,\"lng\":37.655438482761},{\"lat\":55.776365972096,\"lng\":37.655353322625},{\"lat\":55.776384074573,\"lng\":37.655308395624},{\"lat\":55.776468552684,\"lng\":37.655252069235},{\"lat\":55.776493066388,\"lng\":37.655205130577},{\"lat\":55.776814383046,\"lng\":37.654980830848},{\"lat\":55.776825508399,\"lng\":37.654930539429},{\"lat\":55.776893203276,\"lng\":37.654882594943},{\"lat\":55.776904705737,\"lng\":37.654937580228},{\"lat\":55.776872083996,\"lng\":37.654959708452}],[{\"lat\":55.77675064791,\"lng\":37.654705569148},{\"lat\":55.776818908613,\"lng\":37.655001282692}],[{\"lat\":55.776765544593,\"lng\":37.654751166701},{\"lat\":55.776737825444,\"lng\":37.654783353209}],[{\"lat\":55.776804954778,\"lng\":37.65492182225},{\"lat\":55.776778555615,\"lng\":37.654969766736},{\"lat\":55.776820228571,\"lng\":37.654983177781}],[{\"lat\":55.776387468786,\"lng\":37.655321806669},{\"lat\":55.776319584462,\"lng\":37.65500664711}],[{\"lat\":55.776388977325,\"lng\":37.655294314027},{\"lat\":55.776312418888,\"lng\":37.655347287655}],[{\"lat\":55.77638860019,\"lng\":37.654957026243},{\"lat\":55.776458370065,\"lng\":37.65527755022}],[{\"lat\":55.77635729799,\"lng\":37.654980495572},{\"lat\":55.776426690786,\"lng\":37.655297666788}],[{\"lat\":55.776349378152,\"lng\":37.65526548028},{\"lat\":55.776462895674,\"lng\":37.655185684562}],[{\"lat\":55.776368234906,\"lng\":37.65498585999},{\"lat\":55.776311664617,\"lng\":37.655073031783},{\"lat\":55.776340326907,\"lng\":37.655081748962},{\"lat\":55.77640783406,\"lng\":37.655003294349}],[{\"lat\":55.776437250548,\"lng\":37.65514343977},{\"lat\":55.776354280909,\"lng\":37.655203789473}],[{\"lat\":55.776424050845,\"lng\":37.655136063695},{\"lat\":55.776450450247,\"lng\":37.65517629683},{\"lat\":55.776447056039,\"lng\":37.6552862674}],[{\"lat\":55.776393880077,\"lng\":37.654962390661},{\"lat\":55.776358429395,\"lng\":37.655215859413}],[{\"lat\":55.776417639559,\"lng\":37.65505425632},{\"lat\":55.776335424148,\"lng\":37.655108571053}],[{\"lat\":55.776426690786,\"lng\":37.655100524426},{\"lat\":55.776343343989,\"lng\":37.655157521367}],[{\"lat\":55.776384074573,\"lng\":37.655313760042},{\"lat\":55.776410474002,\"lng\":37.654948309064}],[{\"lat\":55.776408588329,\"lng\":37.655071020126},{\"lat\":55.77641613102,\"lng\":37.655020728707},{\"lat\":55.776400291367,\"lng\":37.654961720109}]],\"1\":[[{\"lat\":55.776173255629,\"lng\":37.655146121979},{\"lat\":55.776245665842,\"lng\":37.655516266823}],[{\"lat\":55.776132524825,\"lng\":37.655159533024},{\"lat\":55.776209460752,\"lng\":37.65555113554}],[{\"lat\":55.776099336731,\"lng\":37.655183672905},{\"lat\":55.776177781271,\"lng\":37.655569911003}],[{\"lat\":55.776204935113,\"lng\":37.655167579651},{\"lat\":55.776265276918,\"lng\":37.655459940434}],[{\"lat\":55.776201918021,\"lng\":37.655154168606},{\"lat\":55.77609782818,\"lng\":37.655215859413}],[{\"lat\":55.776266785462,\"lng\":37.655481398106},{\"lat\":55.776158170151,\"lng\":37.65555113554}],[{\"lat\":55.776290922157,\"lng\":37.65541434288},{\"lat\":55.776070674263,\"lng\":37.65555113554},{\"lat\":55.77609782818,\"lng\":37.655349969864},{\"lat\":55.776259242742,\"lng\":37.655253410339}],[{\"lat\":55.776241140207,\"lng\":37.655178308487},{\"lat\":55.776022400586,\"lng\":37.655304372311},{\"lat\":55.776105370932,\"lng\":37.6553606987}],[{\"lat\":55.776227563301,\"lng\":37.655159533024},{\"lat\":55.776287905071,\"lng\":37.655451893806}],[{\"lat\":55.776316567378,\"lng\":37.655041515827},{\"lat\":55.776373891931,\"lng\":37.655323147774}],[{\"lat\":55.776352772369,\"lng\":37.655009329319},{\"lat\":55.776419148097,\"lng\":37.655304372311}],[{\"lat\":55.776417639559,\"lng\":37.654782682657},{\"lat\":55.776515694408,\"lng\":37.655239999294}],[{\"lat\":55.776521728545,\"lng\":37.654891312122},{\"lat\":55.776571510136,\"lng\":37.655138075352}],[{\"lat\":55.77658357839,\"lng\":37.654848396778},{\"lat\":55.776628834313,\"lng\":37.655092477798}],[{\"lat\":55.776633359902,\"lng\":37.654818892479},{\"lat\":55.776681632823,\"lng\":37.655057609081}],[{\"lat\":55.776690683989,\"lng\":37.654775977135},{\"lat\":55.776741973889,\"lng\":37.655025422573}],[{\"lat\":55.776749516516,\"lng\":37.6547062397},{\"lat\":55.776806840431,\"lng\":37.654977142811}],[{\"lat\":55.776796280769,\"lng\":37.65467941761},{\"lat\":55.776853604616,\"lng\":37.65495300293}],[{\"lat\":55.776823434181,\"lng\":37.654714286327},{\"lat\":55.776863410002,\"lng\":37.654903382063}],[{\"lat\":55.776845307748,\"lng\":37.654700875282},{\"lat\":55.776886037808,\"lng\":37.6548846066}],[{\"lat\":55.776865672783,\"lng\":37.654691487551},{\"lat\":55.776909419859,\"lng\":37.654903382063},{\"lat\":55.776845307748,\"lng\":37.654947638512}],[{\"lat\":55.776889809107,\"lng\":37.654674053192},{\"lat\":55.776929030601,\"lng\":37.654849737883}],[{\"lat\":55.776834748097,\"lng\":37.65489667654},{\"lat\":55.776995405348,\"lng\":37.654792070389}],[{\"lat\":55.776814383046,\"lng\":37.654829621315},{\"lat\":55.77723676711,\"lng\":37.654545307159},{\"lat\":55.777241292629,\"lng\":37.65446215868},{\"lat\":55.777571654079,\"lng\":37.654243558645}],[{\"lat\":55.776398782828,\"lng\":37.654982507229},{\"lat\":55.776462141406,\"lng\":37.655260115862}],[{\"lat\":55.776805331908,\"lng\":37.654786705971},{\"lat\":55.776910928378,\"lng\":37.654715627432},{\"lat\":55.776913945416,\"lng\":37.654668688774},{\"lat\":55.776960709472,\"lng\":37.654631137848}],[{\"lat\":55.777530170489,\"lng\":37.654008865356},{\"lat\":55.777002947926,\"lng\":37.654361575842},{\"lat\":55.777070831059,\"lng\":37.654661983252},{\"lat\":55.777141731095,\"lng\":37.654716968536},{\"lat\":55.777252606423,\"lng\":37.654645889997},{\"lat\":55.777297861569,\"lng\":37.654678076506},{\"lat\":55.777612383379,\"lng\":37.65446215868}],[{\"lat\":55.77714550237,\"lng\":37.654715627432},{\"lat\":55.77710326407,\"lng\":37.654628455639},{\"lat\":55.777076110854,\"lng\":37.654311954975}],[{\"lat\":55.777042923563,\"lng\":37.654333412647},{\"lat\":55.777071585316,\"lng\":37.654649913311}],[{\"lat\":55.776925259306,\"lng\":37.654794752598},{\"lat\":55.776825696964,\"lng\":37.654863148928}],[{\"lat\":55.776807594693,\"lng\":37.654700875282},{\"lat\":55.776307516125,\"lng\":37.655056267977}],[{\"lat\":55.776827205486,\"lng\":37.654798775911},{\"lat\":55.776234351755,\"lng\":37.655225247145}],[{\"lat\":55.776837010879,\"lng\":37.654841691256},{\"lat\":55.776250191476,\"lng\":37.655278891325}],[{\"lat\":55.776274328181,\"lng\":37.655324488878},{\"lat\":55.776111405132,\"lng\":37.655437141657}],[{\"lat\":55.776852850355,\"lng\":37.654915452003},{\"lat\":55.7763595608,\"lng\":37.655297666788}]]}";
        
        auto root = jute::parser::parse(jsonRoads);
        unsigned int currentNodeId = 0;
        
        // Перебор этажей, в данном примере у нас их 3 (так как в либе json нет метода получения ключей)))
        for(int floor = 0; floor < root.size(); floor++) {
            //if (floor == 2) {
                auto objRoads = root[std::to_string(floor)];
                // Перебор дорог
                for(int i=0; i<objRoads.size(); i++) {
                    auto objNodes = objRoads[i];
                    std::vector<Node*> road;
                    for(int j=0; j<objNodes.size(); j++) {
                        auto objNode = objNodes[j];                    
                        double lat = objNode["lat"].as_double();
                        double lng = objNode["lng"].as_double();
                        road.push_back(new Node(currentNodeId++, lat, lng, floor));
                    }
                    roads.AddRoad(road);
                }
            //}
        }
        roads.FillGraph(graph);            
    }
}

struct TransitionInfo {
    unsigned int FromID;
    unsigned int ToID;
};

void AddTransitionsExample01(Graph* graph) {
    if(graph != NULL) {
        std::string jsonString = "[{\"transitionId\":90,\"transitionTypeId\":8,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u0412\u044b\u0445\u043e\u0434\",\"floor\":1,\"radius\":100,\"transitionFrom\":0,\"transitionTo\":0,\"location\":{\"lat\":\"55.777013507532\",\"lng\":\"37.6546834409237\"}},{\"transitionId\":93,\"transitionTypeId\":8,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u0412\u0445\u043e\u0434\",\"floor\":1,\"radius\":100,\"transitionFrom\":0,\"transitionTo\":0,\"location\":{\"lat\":\"55.7759997722792\",\"lng\":\"37.6555082201958\"}},{\"transitionId\":97,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043001\",\"floor\":0,\"radius\":284,\"transitionFrom\":0,\"transitionTo\":105,\"location\":{\"lat\":\"55.7766808785588\",\"lng\":\"37.6550978422165\"}},{\"transitionId\":98,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u043d\u0438\u0446\u043002\",\"floor\":0,\"radius\":284,\"transitionFrom\":0,\"transitionTo\":104,\"location\":{\"lat\":\"55.7766499537255\",\"lng\":\"37.6549516618252\"}},{\"transitionId\":99,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043003\",\"floor\":0,\"radius\":246,\"transitionFrom\":0,\"transitionTo\":106,\"location\":{\"lat\":\"55.7766114862155\",\"lng\":\"37.6552279293537\"}},{\"transitionId\":100,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043004\",\"floor\":0,\"radius\":359,\"transitionFrom\":0,\"transitionTo\":107,\"location\":{\"lat\":\"55.7764221651724\",\"lng\":\"37.6551447808742\"}},{\"transitionId\":101,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043005\",\"floor\":0,\"radius\":171,\"transitionFrom\":0,\"transitionTo\":108,\"location\":{\"lat\":\"55.7762905450208\",\"lng\":\"37.6553526520729\"}},{\"transitionId\":102,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043007\",\"floor\":0,\"radius\":171,\"transitionFrom\":0,\"transitionTo\":109,\"location\":{\"lat\":\"55.7762796080827\",\"lng\":\"37.6552849262953\"}},{\"transitionId\":104,\"transitionTypeId\":2,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043012\",\"floor\":1,\"radius\":322,\"transitionFrom\":98,\"transitionTo\":110,\"location\":{\"lat\":\"55.7768339938356\",\"lng\":\"37.6546646654606\"}},{\"transitionId\":105,\"transitionTypeId\":2,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043011\",\"floor\":1,\"radius\":284,\"transitionFrom\":97,\"transitionTo\":111,\"location\":{\"lat\":\"55.7768792494673\",\"lng\":\"37.6549355685711\"}},{\"transitionId\":106,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043013\",\"floor\":1,\"radius\":265,\"transitionFrom\":99,\"transitionTo\":112,\"location\":{\"lat\":\"55.7768272054864\",\"lng\":\"37.6552198827267\"}},{\"transitionId\":107,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043013\",\"floor\":1,\"radius\":265,\"transitionFrom\":100,\"transitionTo\":0,\"location\":{\"lat\":\"55.7764425304284\",\"lng\":\"37.6548470556736\"}},{\"transitionId\":108,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u043d\u0438\u0446\u043014\",\"floor\":1,\"radius\":246,\"transitionFrom\":101,\"transitionTo\":113,\"location\":{\"lat\":\"55.7762856422558\",\"lng\":\"37.6553821563721\"}},{\"transitionId\":109,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043015\",\"floor\":1,\"radius\":265,\"transitionFrom\":102,\"transitionTo\":114,\"location\":{\"lat\":\"55.7762396316624\",\"lng\":\"37.6551756262779\"}},{\"transitionId\":110,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043022\",\"floor\":2,\"radius\":416,\"transitionFrom\":104,\"transitionTo\":0,\"location\":{\"lat\":\"55.7768585073093\",\"lng\":\"37.6546465605497\"}},{\"transitionId\":111,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043021\",\"floor\":2,\"radius\":397,\"transitionFrom\":105,\"transitionTo\":0,\"location\":{\"lat\":\"55.7769037629125\",\"lng\":\"37.6549228280783\"}},{\"transitionId\":112,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043033\",\"floor\":2,\"radius\":454,\"transitionFrom\":106,\"transitionTo\":0,\"location\":{\"lat\":\"55.7767155746841\",\"lng\":\"37.6551709324122\"}},{\"transitionId\":113,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043034\",\"floor\":2,\"radius\":341,\"transitionFrom\":108,\"transitionTo\":0,\"location\":{\"lat\":\"55.7761691071227\",\"lng\":\"37.655511572957\"}},{\"transitionId\":114,\"transitionTypeId\":1,\"directionTypeId\":3,\"shoppingCenterId\":57,\"shopId\":0,\"transitionShopId\":0,\"name\":\"\u041b\u0435\u0441\u0442\u043d\u0438\u0446\u043035\",\"floor\":2,\"radius\":359,\"transitionFrom\":109,\"transitionTo\":0,\"location\":{\"lat\":\"55.7761121594067\",\"lng\":\"37.6552715152502\"}}]";
        
        
        auto root = jute::parser::parse(jsonString);
        
        std::vector<TransitionInfo> forNextEdges;
        
#ifdef DEBUG_TEST_TRANSITIONS
        printf("Transition layerId: %d\n", layerId);
#endif
        
        unsigned int crossLayerId = graph->GetMaxNodeID()+1;
        unsigned int layerId = crossLayerId+root.size()+1000;
        
        for(int i=0; i<root.size(); i++) {
            auto transition = root[i];
            auto transitionId = transition["transitionId"].as_int();
            auto name = transition["name"].as_string();
            auto floor = transition["floor"].as_int();
            auto location = transition["location"];
            if(transition.get_type() == jute::JOBJECT) {
                double lat = location["lat"].as_double();
                double lng = location["lng"].as_double();
                
                // Поиск точек рядом на этаже 
                Node* nereast = graph->GenNewNearestNodeInEdges(crossLayerId+i, lat, lng, floor);
                                //graph->GetNearestNode(lat, lng, floor);
                
                if(nereast != NULL) {
                    // Присоединяем переход к ближайшей ноде
                    Node *node = graph->AddNode((unsigned int)(layerId+transitionId), name, lat, lng, floor);
                    if(node != NULL) {
                        // Два направления
                        graph->AddEdge(nereast->GetID(), node->GetID());
                        graph->AddEdge(node->GetID(), nereast->GetID());
                        
                        // Добавляем в очередь переходы между этажами
                        auto transitionFrom = transition["transitionFrom"].as_int();
                        auto transitionTo = transition["transitionTo"].as_int();
                        if(transitionFrom > 0) {
                            TransitionInfo infoForward;
                            infoForward.FromID = (unsigned int)layerId+transitionFrom;
                            infoForward.ToID = (unsigned int)layerId+transitionId;
                            forNextEdges.push_back(infoForward);
                            
                            // В обратную сторону
                            TransitionInfo infoBackward;
                            infoBackward.FromID = (unsigned int)layerId+transitionId;
                            infoBackward.ToID = (unsigned int)layerId+transitionFrom;
                            forNextEdges.push_back(infoBackward);
                        }
                        if(transitionTo > 0) {
                            TransitionInfo infoForward;
                            infoForward.FromID = (unsigned int)layerId+transitionId;
                            infoForward.ToID = (unsigned int)layerId+transitionTo;
                            forNextEdges.push_back(infoForward);
                            
                            // В обратную сторону
                            TransitionInfo infoBackward;
                            infoBackward.FromID = (unsigned int)layerId+transitionTo;
                            infoBackward.ToID = (unsigned int)layerId+transitionId;
                            forNextEdges.push_back(infoBackward);
                        }
                    } else {
                        printf("Error Add Transition\n");
                    }
                } else {
                    printf("Error Find Nearest Node For Transition\n");
                }
            }
        }
        
        //Перебираем очередь
        for(int j=0;j<forNextEdges.size();j++) {
#ifdef DEBUG_TEST_TRANSITIONS
            Node *from = graph->GetNode(forNextEdges[j].FromID);
            Node *to =graph->GetNode(forNextEdges[j].ToID);
            if(from != NULL && to != NULL) {
                printf("Add Transition Edge: level %d (id_%d) -> level %d (id_%d))\n", from->GetLevel(), from->GetID(), to->GetLevel(), to->GetID());
            } else {
                printf("Error Add Transition Edge (%d -> %d)\n", forNextEdges[j].FromID, forNextEdges[j].ToID);
            }
#endif
            graph->AddEdge(forNextEdges[j].FromID, forNextEdges[j].ToID);
        }
    }
}
