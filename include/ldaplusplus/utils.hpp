#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <memory>
#include <mutex>

#include <Eigen/Core>

namespace ldaplusplus {
namespace math_utils {


static const std::array<double, 1024> exp_lut = {
    1.000000000000000000e+00, 1.000977995032110268e+00, 1.001956946538503423e+00,
    1.002936855454606535e+00, 1.003917722716761274e+00, 1.004899549262225911e+00,
    1.005882336029174207e+00, 1.006866083956698077e+00, 1.007850793984808035e+00,
    1.008836467054433639e+00, 1.009823104107424596e+00, 1.010810706086551880e+00,
    1.011799273935508392e+00, 1.012788808598910073e+00, 1.013779311022296792e+00,
    1.014770782152132789e+00, 1.015763222935808230e+00, 1.016756634321639652e+00,
    1.017751017258871515e+00, 1.018746372697675762e+00, 1.019742701589154477e+00,
    1.020740004885339447e+00, 1.021738283539193493e+00, 1.022737538504611798e+00,
    1.023737770736421915e+00, 1.024738981190385756e+00, 1.025741170823199822e+00,
    1.026744340592495863e+00, 1.027748491456842661e+00, 1.028753624375746245e+00,
    1.029759740309651228e+00, 1.030766840219941249e+00, 1.031774925068940307e+00,
    1.032783995819913647e+00, 1.033794053437068428e+00, 1.034805098885555052e+00,
    1.035817133131467616e+00, 1.036830157141844788e+00, 1.037844171884671818e+00,
    1.038859178328879640e+00, 1.039875177444347321e+00, 1.040892170201902722e+00,
    1.041910157573322726e+00, 1.042929140531334564e+00, 1.043949120049617374e+00,
    1.044970097102801754e+00, 1.045992072666471984e+00, 1.047015047717166691e+00,
    1.048039023232378630e+00, 1.049064000190557788e+00, 1.050089979571109833e+00,
    1.051116962354399220e+00, 1.052144949521748529e+00, 1.053173942055440682e+00,
    1.054203940938718942e+00, 1.055234947155788250e+00, 1.056266961691815665e+00,
    1.057299985532932585e+00, 1.058334019666233861e+00, 1.059369065079780903e+00,
    1.060405122762600127e+00, 1.061442193704686288e+00, 1.062480278897001806e+00,
    1.063519379331478110e+00, 1.064559496001017402e+00, 1.065600629899492224e+00,
    1.066642782021747449e+00, 1.067685953363600948e+00, 1.068730144921844483e+00,
    1.069775357694244589e+00, 1.070821592679543466e+00, 1.071868850877460533e+00,
    1.072917133288692426e+00, 1.073966440914914777e+00, 1.075016774758782656e+00,
    1.076068135823932126e+00, 1.077120525114980021e+00, 1.078173943637526611e+00,
    1.079228392398154712e+00, 1.080283872404432577e+00, 1.081340384664913001e+00,
    1.082397930189135327e+00, 1.083456509987626770e+00, 1.084516125071902204e+00,
    1.085576776454466152e+00, 1.086638465148812793e+00, 1.087701192169428399e+00,
    1.088764958531790450e+00, 1.089829765252370297e+00, 1.090895613348632942e+00,
    1.091962503839038812e+00, 1.093030437743044203e+00, 1.094099416081102172e+00,
    1.095169439874664308e+00, 1.096240510146180736e+00, 1.097312627919101669e+00,
    1.098385794217878519e+00, 1.099460010067964122e+00, 1.100535276495814507e+00,
    1.101611594528889571e+00, 1.102688965195653736e+00, 1.103767389525577958e+00,
    1.104846868549139272e+00, 1.105927403297823020e+00, 1.107008994804122848e+00,
    1.108091644101542705e+00, 1.109175352224596844e+00, 1.110260120208811818e+00,
    1.111345949090726037e+00, 1.112432839907892657e+00, 1.113520793698878908e+00,
    1.114609811503268100e+00, 1.115699894361659616e+00, 1.116791043315671139e+00,
    1.117883259407939311e+00, 1.118976543682119518e+00, 1.120070897182888547e+00,
    1.121166320955944595e+00, 1.122262816048008816e+00, 1.123360383506825988e+00,
    1.124459024381165184e+00, 1.125558739720821544e+00, 1.126659530576616719e+00,
    1.127761398000400428e+00, 1.128864343045050456e+00, 1.129968366764475096e+00,
    1.131073470213612486e+00, 1.132179654448433048e+00, 1.133286920525939934e+00,
    1.134395269504169912e+00, 1.135504702442194480e+00, 1.136615220400120752e+00,
    1.137726824439093010e+00, 1.138839515621292930e+00, 1.139953295009941581e+00,
    1.141068163669298974e+00, 1.142184122664666734e+00, 1.143301173062388099e+00,
    1.144419315929849024e+00, 1.145538552335479299e+00, 1.146658883348754321e+00,
    1.147780310040194429e+00, 1.148902833481367791e+00, 1.150026454744889959e+00,
    1.151151174904425867e+00, 1.152276995034690277e+00, 1.153403916211449332e+00,
    1.154531939511520555e+00, 1.155661066012775517e+00, 1.156791296794139168e+00,
    1.157922632935592278e+00, 1.159055075518171440e+00, 1.160188625623970404e+00,
    1.161323284336141404e+00, 1.162459052738896270e+00, 1.163595931917506432e+00,
    1.164733922958305579e+00, 1.165873026948688995e+00, 1.167013244977116226e+00,
    1.168154578133110855e+00, 1.169297027507261832e+00, 1.170440594191225259e+00,
    1.171585279277724378e+00, 1.172731083860551582e+00, 1.173878009034568626e+00,
    1.175026055895707744e+00, 1.176175225540974090e+00, 1.177325519068444182e+00,
    1.178476937577269901e+00, 1.179629482167676935e+00, 1.180783153940967667e+00,
    1.181937953999521618e+00, 1.183093883446795669e+00, 1.184250943387326727e+00,
    1.185409134926731500e+00, 1.186568459171707834e+00, 1.187728917230036485e+00,
    1.188890510210581342e+00, 1.190053239223290316e+00, 1.191217105379197339e+00,
    1.192382109790423028e+00, 1.193548253570175355e+00, 1.194715537832750751e+00,
    1.195883963693536112e+00, 1.197053532269008791e+00, 1.198224244676737937e+00,
    1.199396102035385825e+00, 1.200569105464708963e+00, 1.201743256085558542e+00,
    1.202918555019882207e+00, 1.204095003390724949e+00, 1.205272602322229991e+00,
    1.206451352939639676e+00, 1.207631256369297246e+00, 1.208812313738647726e+00,
    1.209994526176237706e+00, 1.211177894811718669e+00, 1.212362420775846328e+00,
    1.213548105200482397e+00, 1.214734949218595261e+00, 1.215922953964261755e+00,
    1.217112120572667600e+00, 1.218302450180108965e+00, 1.219493943923992907e+00,
    1.220686602942839150e+00, 1.221880428376280747e+00, 1.223075421365065640e+00,
    1.224271583051056878e+00, 1.225468914577234614e+00, 1.226667417087696776e+00,
    1.227867091727659954e+00, 1.229067939643461393e+00, 1.230269961982558780e+00,
    1.231473159893532010e+00, 1.232677534526085195e+00, 1.233883087031045545e+00,
    1.235089818560366925e+00, 1.236297730267128969e+00, 1.237506823305539294e+00,
    1.238717098830934837e+00, 1.239928557999781411e+00, 1.241141201969676811e+00,
    1.242355031899350593e+00, 1.243570048948665407e+00, 1.244786254278618332e+00,
    1.246003649051341977e+00, 1.247222234430105381e+00, 1.248442011579315558e+00,
    1.249662981664517947e+00, 1.250885145852397962e+00, 1.252108505310782105e+00,
    1.253333061208639077e+00, 1.254558814716080661e+00, 1.255785767004363285e+00,
    1.257013919245888234e+00, 1.258243272614204322e+00, 1.259473828284007002e+00,
    1.260705587431141694e+00, 1.261938551232603123e+00, 1.263172720866537091e+00,
    1.264408097512241813e+00, 1.265644682350168804e+00, 1.266882476561923987e+00,
    1.268121481330269251e+00, 1.269361697839122449e+00, 1.270603127273560284e+00,
    1.271845770819817423e+00, 1.273089629665289824e+00, 1.274334704998533629e+00,
    1.275580998009267830e+00, 1.276828509888375152e+00, 1.278077241827902721e+00,
    1.279327195021063623e+00, 1.280578370662237786e+00, 1.281830769946973314e+00,
    1.283084394071987600e+00, 1.284339244235168209e+00, 1.285595321635574440e+00,
    1.286852627473438426e+00, 1.288111162950165367e+00, 1.289370929268336408e+00,
    1.290631927631708420e+00, 1.291894159245215112e+00, 1.293157625314969250e+00,
    1.294422327048262655e+00, 1.295688265653568649e+00, 1.296955442340541387e+00,
    1.298223858320018742e+00, 1.299493514804022753e+00, 1.300764413005760733e+00,
    1.302036554139626157e+00, 1.303309939421200658e+00, 1.304584570067254479e+00,
    1.305860447295748017e+00, 1.307137572325832497e+00, 1.308415946377851968e+00,
    1.309695570673343301e+00, 1.310976446435038634e+00, 1.312258574886865814e+00,
    1.313541957253949288e+00, 1.314826594762612100e+00, 1.316112488640376332e+00,
    1.317399640115964887e+00, 1.318688050419302149e+00, 1.319977720781515540e+00,
    1.321268652434935964e+00, 1.322560846613100471e+00, 1.323854304550751593e+00,
    1.325149027483840003e+00, 1.326445016649525188e+00, 1.327742273286175889e+00,
    1.329040798633372544e+00, 1.330340593931907733e+00, 1.331641660423787732e+00,
    1.332943999352233400e+00, 1.334247611961681068e+00, 1.335552499497784540e+00,
    1.336858663207415976e+00, 1.338166104338666340e+00, 1.339474824140847842e+00,
    1.340784823864494379e+00, 1.342096104761362874e+00, 1.343408668084433932e+00,
    1.344722515087914516e+00, 1.346037647027237272e+00, 1.347354065159063197e+00,
    1.348671770741282527e+00, 1.349990765033014739e+00, 1.351311049294611877e+00,
    1.352632624787657667e+00, 1.353955492774970404e+00, 1.355279654520602728e+00,
    1.356605111289844068e+00, 1.357931864349220863e+00, 1.359259914966498561e+00,
    1.360589264410682508e+00, 1.361919913952018835e+00, 1.363251864861995788e+00,
    1.364585118413345954e+00, 1.365919675880045814e+00, 1.367255538537318182e+00,
    1.368592707661632879e+00, 1.369931184530708501e+00, 1.371270970423512425e+00,
    1.372612066620263693e+00, 1.373954474402432790e+00, 1.375298195052744088e+00,
    1.376643229855176065e+00, 1.377989580094962641e+00, 1.379337247058595173e+00,
    1.380686232033823124e+00, 1.382036536309655395e+00, 1.383388161176360986e+00,
    1.384741107925471670e+00, 1.386095377849781762e+00, 1.387450972243349678e+00,
    1.388807892401500377e+00, 1.390166139620824470e+00, 1.391525715199181779e+00,
    1.392886620435700218e+00, 1.394248856630779132e+00, 1.395612425086089514e+00,
    1.396977327104575117e+00, 1.398343563990454008e+00, 1.399711137049220122e+00,
    1.401080047587643707e+00, 1.402450296913773320e+00, 1.403821886336936497e+00,
    1.405194817167741750e+00, 1.406569090718078785e+00, 1.407944708301120951e+00,
    1.409321671231325457e+00, 1.410699980824435151e+00, 1.412079638397479409e+00,
    1.413460645268776350e+00, 1.414843002757932622e+00, 1.416226712185845837e+00,
    1.417611774874705466e+00, 1.418998192147993942e+00, 1.420385965330488220e+00,
    1.421775095748260442e+00, 1.423165584728680377e+00, 1.424557433600415424e+00,
    1.425950643693432385e+00, 1.427345216338999023e+00, 1.428741152869684949e+00,
    1.430138454619362953e+00, 1.431537122923210559e+00, 1.432937159117710912e+00,
    1.434338564540654337e+00, 1.435741340531139221e+00, 1.437145488429574014e+00,
    1.438551009577677897e+00, 1.439957905318482112e+00, 1.441366176996331516e+00,
    1.442775825956885694e+00, 1.444186853547120286e+00, 1.445599261115328327e+00,
    1.447013050011121349e+00, 1.448428221585431164e+00, 1.449844777190509859e+00,
    1.451262718179933353e+00, 1.452682045908600061e+00, 1.454102761732734450e+00,
    1.455524867009887036e+00, 1.456948363098935717e+00, 1.458373251360087552e+00,
    1.459799533154880313e+00, 1.461227209846182706e+00, 1.462656282798196594e+00,
    1.464086753376458105e+00, 1.465518622947838745e+00, 1.466951892880546948e+00,
    1.468386564544128747e+00, 1.469822639309470436e+00, 1.471260118548798346e+00,
    1.472699003635681070e+00, 1.474139295945030570e+00, 1.475580996853103288e+00,
    1.477024107737501923e+00, 1.478468629977176318e+00, 1.479914564952424794e+00,
    1.481361914044895922e+00, 1.482810678637589197e+00, 1.484260860114857028e+00,
    1.485712459862404966e+00, 1.487165479267294810e+00, 1.488619919717944162e+00,
    1.490075782604128651e+00, 1.491533069316983262e+00, 1.492991781249003447e+00,
    1.494451919794046457e+00, 1.495913486347332677e+00, 1.497376482305447176e+00,
    1.498840909066340599e+00, 1.500306768029331161e+00, 1.501774060595105320e+00,
    1.503242788165719546e+00, 1.504712952144601212e+00, 1.506184553936550596e+00,
    1.507657594947741764e+00, 1.509132076585724125e+00, 1.510608000259423100e+00,
    1.512085367379143008e+00, 1.513564179356566397e+00, 1.515044437604757155e+00,
    1.516526143538160953e+00, 1.518009298572606580e+00, 1.519493904125307715e+00,
    1.520979961614864262e+00, 1.522467472461262794e+00, 1.523956438085879439e+00,
    1.525446859911479880e+00, 1.526938739362221575e+00, 1.528432077863654648e+00,
    1.529926876842723216e+00, 1.531423137727767392e+00, 1.532920861948523950e+00,
    1.534420050936127655e+00, 1.535920706123113710e+00, 1.537422828943417308e+00,
    1.538926420832376962e+00, 1.540431483226734288e+00, 1.541938017564636221e+00,
    1.543446025285636569e+00, 1.544955507830696240e+00, 1.546466466642186122e+00,
    1.547978903163887310e+00, 1.549492818840993102e+00, 1.551008215120110112e+00,
    1.552525093449259819e+00, 1.554043455277879682e+00, 1.555563302056824915e+00,
    1.557084635238369597e+00, 1.558607456276208003e+00, 1.560131766625456162e+00,
    1.561657567742653185e+00, 1.563184861085763044e+00, 1.564713648114174793e+00,
    1.566243930288705677e+00, 1.567775709071600909e+00, 1.569308985926536115e+00,
    1.570843762318618220e+00, 1.572380039714387445e+00, 1.573917819581817312e+00,
    1.575457103390318192e+00, 1.576997892610736862e+00, 1.578540188715358505e+00,
    1.580083993177908486e+00, 1.581629307473553459e+00, 1.583176133078902703e+00,
    1.584724471472009455e+00, 1.586274324132372682e+00, 1.587825692540938194e+00,
    1.589378578180100199e+00, 1.590932982533702855e+00, 1.592488907087041161e+00,
    1.594046353326863175e+00, 1.595605322741370236e+00, 1.597165816820220074e+00,
    1.598727837054526590e+00, 1.600291384936862515e+00, 1.601856461961259637e+00,
    1.603423069623211461e+00, 1.604991209419673881e+00, 1.606560882849066951e+00,
    1.608132091411276221e+00, 1.609704836607653400e+00, 1.611279119941019689e+00,
    1.612854942915664891e+00, 1.614432307037350967e+00, 1.616011213813311809e+00,
    1.617591664752255909e+00, 1.619173661364366579e+00, 1.620757205161304615e+00,
    1.622342297656209409e+00, 1.623928940363699613e+00, 1.625517134799875363e+00,
    1.627106882482319827e+00, 1.628698184930099879e+00, 1.630291043663768535e+00,
    1.631885460205365623e+00, 1.633481436078419557e+00, 1.635078972807948450e+00,
    1.636678071920462774e+00, 1.638278734943964698e+00, 1.639880963407951864e+00,
    1.641484758843416936e+00, 1.643090122782850715e+00, 1.644697056760241693e+00,
    1.646305562311079607e+00, 1.647915640972355433e+00, 1.649527294282563172e+00,
    1.651140523781701841e+00, 1.652755331011276363e+00, 1.654371717514299123e+00,
    1.655989684835291964e+00, 1.657609234520286634e+00, 1.659230368116827670e+00,
    1.660853087173972398e+00, 1.662477393242293600e+00, 1.664103287873880177e+00,
    1.665730772622339151e+00, 1.667359849042796993e+00, 1.668990518691900959e+00,
    1.670622783127820865e+00, 1.672256643910250196e+00, 1.673892102600407883e+00,
    1.675529160761039638e+00, 1.677167819956419725e+00, 1.678808081752352521e+00,
    1.680449947716172732e+00, 1.682093419416749169e+00, 1.683738498424484087e+00,
    1.685385186311316064e+00, 1.687033484650720894e+00, 1.688683395017712918e+00,
    1.690334918988847468e+00, 1.691988058142221085e+00, 1.693642814057473966e+00,
    1.695299188315791517e+00, 1.696957182499905015e+00, 1.698616798194093835e+00,
    1.700278036984186558e+00, 1.701940900457563410e+00, 1.703605390203156267e+00,
    1.705271507811451093e+00, 1.706939254874489942e+00, 1.708608632985871179e+00,
    1.710279643740752142e+00, 1.711952288735850036e+00, 1.713626569569443481e+00,
    1.715302487841374512e+00, 1.716980045153049694e+00, 1.718659243107441892e+00,
    1.720340083309091384e+00, 1.722022567364107859e+00, 1.723706696880171751e+00,
    1.725392473466535792e+00, 1.727079898734026564e+00, 1.728768974295046057e+00,
    1.730459701763572999e+00, 1.732152082755164635e+00, 1.733846118886958720e+00,
    1.735541811777673971e+00, 1.737239163047612056e+00, 1.738938174318660046e+00,
    1.740638847214290630e+00, 1.742341183359564338e+00, 1.744045184381131319e+00,
    1.745750851907231782e+00, 1.747458187567699328e+00, 1.749167192993960951e+00,
    1.750877869819039478e+00, 1.752590219677554240e+00, 1.754304244205723951e+00,
    1.756019945041367158e+00, 1.757737323823904463e+00, 1.759456382194358959e+00,
    1.761177121795359790e+00, 1.762899544271141927e+00, 1.764623651267548610e+00,
    1.766349444432032456e+00, 1.768076925413657907e+00, 1.769806095863101225e+00,
    1.771536957432653825e+00, 1.773269511776222718e+00, 1.775003760549332510e+00,
    1.776739705409126735e+00, 1.778477348014370074e+00, 1.780216690025448578e+00,
    1.781957733104373443e+00, 1.783700478914779897e+00, 1.785444929121931423e+00,
    1.787191085392719092e+00, 1.788938949395664890e+00, 1.790688522800922389e+00,
    1.792439807280278741e+00, 1.794192804507155570e+00, 1.795947516156611412e+00,
    1.797703943905343493e+00, 1.799462089431687950e+00, 1.801221954415622939e+00,
    1.802983540538769303e+00, 1.804746849484392790e+00, 1.806511882937405389e+00,
    1.808278642584366214e+00, 1.810047130113484837e+00, 1.811817347214621288e+00,
    1.813589295579288496e+00, 1.815362976900653402e+00, 1.817138392873539177e+00,
    1.818915545194426331e+00, 1.820694435561454716e+00, 1.822475065674424632e+00,
    1.824257437234799051e+00, 1.826041551945704944e+00, 1.827827411511934841e+00,
    1.829615017639948382e+00, 1.831404372037874539e+00, 1.833195476415512726e+00,
    1.834988332484334128e+00, 1.836782941957484150e+00, 1.838579306549783521e+00,
    1.840377427977729852e+00, 1.842177307959500077e+00, 1.843978948214950675e+00,
    1.845782350465620780e+00, 1.847587516434733068e+00, 1.849394447847195311e+00,
    1.851203146429602153e+00, 1.853013613910237112e+00, 1.854825852019074128e+00,
    1.856639862487778458e+00, 1.858455647049709336e+00, 1.860273207439921306e+00,
    1.862092545395165555e+00, 1.863913662653891468e+00, 1.865736560956249512e+00,
    1.867561242044091241e+00, 1.869387707660971953e+00, 1.871215959552152475e+00,
    1.873045999464600042e+00, 1.874877829146990305e+00, 1.876711450349709764e+00,
    1.878546864824856444e+00, 1.880384074326241439e+00, 1.882223080609391808e+00,
    1.884063885431551011e+00, 1.885906490551681580e+00, 1.887750897730465560e+00,
    1.889597108730307617e+00, 1.891445125315335929e+00, 1.893294949251403514e+00,
    1.895146582306090899e+00, 1.897000026248707005e+00, 1.898855282850291371e+00,
    1.900712353883615258e+00, 1.902571241123184098e+00, 1.904431946345238380e+00,
    1.906294471327756090e+00, 1.908158817850454048e+00, 1.910024987694789234e+00,
    1.911892982643961236e+00, 1.913762804482913360e+00, 1.915634454998335068e+00,
    1.917507935978662870e+00, 1.919383249214082099e+00, 1.921260396496529133e+00,
    1.923139379619692946e+00, 1.925020200379016666e+00, 1.926902860571699128e+00,
    1.928787361996697314e+00, 1.930673706454727245e+00, 1.932561895748265979e+00,
    1.934451931681553383e+00, 1.936343816060594136e+00, 1.938237550693158839e+00,
    1.940133137388786233e+00, 1.942030577958784976e+00, 1.943929874216234976e+00,
    1.945831027975989169e+00, 1.947734041054675735e+00, 1.949638915270699435e+00,
    1.951545652444242940e+00, 1.953454254397269940e+00, 1.955364722953525147e+00,
    1.957277059938537400e+00, 1.959191267179620555e+00, 1.961107346505876148e+00,
    1.963025299748193842e+00, 1.964945128739254310e+00, 1.966866835313530570e+00,
    1.968790421307289762e+00, 1.970715888558594475e+00, 1.972643238907305641e+00,
    1.974572474195082972e+00, 1.976503596265387408e+00, 1.978436606963483113e+00,
    1.980371508136438585e+00, 1.982308301633128655e+00, 1.984246989304236930e+00,
    1.986187573002256235e+00, 1.988130054581491502e+00, 1.990074435898061544e+00,
    1.992020718809899504e+00, 1.993968905176756401e+00, 1.995918996860201577e+00,
    1.997870995723625365e+00, 1.999824903632240414e+00, 2.001780722453083250e+00,
    2.003738454055016494e+00, 2.005698100308730414e+00, 2.007659663086745372e+00,
    2.009623144263412708e+00, 2.011588545714916076e+00, 2.013555869319274994e+00,
    2.015525116956345730e+00, 2.017496290507822643e+00, 2.019469391857240392e+00,
    2.021444422889975279e+00, 2.023421385493248792e+00, 2.025400281556126725e+00,
    2.027381112969523613e+00, 2.029363881626201849e+00, 2.031348589420776563e+00,
    2.033335238249714294e+00, 2.035323830011336987e+00, 2.037314366605823768e+00,
    2.039306849935211385e+00, 2.041301281903396436e+00, 2.043297664416138471e+00,
    2.045295999381059993e+00, 2.047296288707649570e+00, 2.049298534307263164e+00,
    2.051302738093126798e+00, 2.053308901980336110e+00, 2.055317027885860792e+00,
    2.057327117728544597e+00, 2.059339173429108882e+00, 2.061353196910152619e+00,
    2.063369190096155492e+00, 2.065387154913478795e+00, 2.067407093290368536e+00,
    2.069429007156956324e+00, 2.071452898445260704e+00, 2.073478769089190710e+00,
    2.075506621024545861e+00, 2.077536456189019720e+00, 2.079568276522200776e+00,
    2.081602083965573780e+00, 2.083637880462522407e+00, 2.085675667958331481e+00,
    2.087715448400187856e+00, 2.089757223737183089e+00, 2.091800995920314765e+00,
    2.093846766902488277e+00, 2.095894538638519045e+00, 2.097944313085134738e+00,
    2.099996092200975717e+00, 2.102049877946599477e+00, 2.104105672284479311e+00,
    2.106163477179008314e+00, 2.108223294596501596e+00, 2.110285126505196285e+00,
    2.112348974875254637e+00, 2.114414841678765811e+00, 2.116482728889747644e+00,
    2.118552638484149320e+00, 2.120624572439850919e+00, 2.122698532736667865e+00,
    2.124774521356352253e+00, 2.126852540282593296e+00, 2.128932591501020877e+00,
    2.131014676999206436e+00, 2.133098798766665638e+00, 2.135184958794859700e+00,
    2.137273159077198059e+00, 2.139363401609037929e+00, 2.141455688387690071e+00,
    2.143550021412417461e+00, 2.145646402684438847e+00, 2.147744834206929632e+00,
    2.149845317985024540e+00, 2.151947856025819394e+00, 2.154052450338372893e+00,
    2.156159102933708827e+00, 2.158267815824817415e+00, 2.160378591026657524e+00,
    2.162491430556158889e+00, 2.164606336432223888e+00, 2.166723310675729319e+00,
    2.168842355309527736e+00, 2.170963472358450552e+00, 2.173086663849310263e+00,
    2.175211931810900001e+00, 2.177339278273997980e+00, 2.179468705271368378e+00,
    2.181600214837763563e+00, 2.183733809009925864e+00, 2.185869489826588907e+00,
    2.188007259328480725e+00, 2.190147119558325084e+00, 2.192289072560843710e+00,
    2.194433120382758062e+00, 2.196579265072790665e+00, 2.198727508681668219e+00,
    2.200877853262122930e+00, 2.203030300868894731e+00, 2.205184853558733060e+00,
    2.207341513390398191e+00, 2.209500282424664785e+00, 2.211661162724322338e+00,
    2.213824156354178285e+00, 2.215989265381058448e+00, 2.218156491873810587e+00,
    2.220325837903306176e+00, 2.222497305542441737e+00, 2.224670896866141057e+00,
    2.226846613951356524e+00, 2.229024458877072234e+00, 2.231204433724306213e+00,
    2.233386540576111301e+00, 2.235570781517576489e+00, 2.237757158635831800e+00,
    2.239945674020046962e+00, 2.242136329761435398e+00, 2.244329127953256009e+00,
    2.246524070690814501e+00, 2.248721160071466496e+00, 2.250920398194617533e+00,
    2.253121787161727507e+00, 2.255325329076311114e+00, 2.257531026043940514e+00,
    2.259738880172246223e+00, 2.261948893570921104e+00, 2.264161068351720818e+00,
    2.266375406628466482e+00, 2.268591910517046006e+00, 2.270810582135417199e+00,
    2.273031423603609102e+00, 2.275254437043724209e+00, 2.277479624579939799e+00,
    2.279706988338511042e+00, 2.281936530447773226e+00, 2.284168253038142193e+00,
    2.286402158242117455e+00, 2.288638248194284408e+00, 2.290876525031316113e+00,
    2.293116990891975071e+00, 2.295359647917114998e+00, 2.297604498249684379e+00,
    2.299851544034726469e+00, 2.302100787419383732e+00, 2.304352230552896952e+00,
    2.306605875586610122e+00, 2.308861724673969995e+00, 2.311119779970530974e+00,
    2.313380043633953775e+00, 2.315642517824010760e+00, 2.317907204702585933e+00,
    2.320174106433678052e+00, 2.322443225183401072e+00, 2.324714563119988586e+00,
    2.326988122413794269e+00, 2.329263905237294541e+00, 2.331541913765090346e+00,
    2.333822150173909371e+00, 2.336104616642608711e+00, 2.338389315352174869e+00,
    2.340676248485729083e+00, 2.342965418228526886e+00, 2.345256826767960323e+00,
    2.347550476293561950e+00, 2.349846368997005275e+00, 2.352144507072106983e+00,
    2.354444892714828708e+00, 2.356747528123281477e+00, 2.359052415497723931e+00,
    2.361359557040568546e+00, 2.363668954956380297e+00, 2.365980611451881099e+00,
    2.368294528735950255e+00, 2.370610709019628004e+00, 2.372929154516116412e+00,
    2.375249867440782925e+00, 2.377572850011160810e+00, 2.379898104446951823e+00,
    2.382225632970029761e+00, 2.384555437804440015e+00, 2.386887521176404459e+00,
    2.389221885314321003e+00, 2.391558532448767593e+00, 2.393897464812503539e+00,
    2.396238684640471295e+00, 2.398582194169800452e+00, 2.400927995639806412e+00,
    2.403276091291996597e+00, 2.405626483370069568e+00, 2.407979174119918575e+00,
    2.410334165789632888e+00, 2.412691460629500906e+00, 2.415051060892011492e+00,
    2.417412968831856190e+00, 2.419777186705932781e+00, 2.422143716773345279e+00,
    2.424512561295406599e+00, 2.426883722535642551e+00, 2.429257202759791401e+00,
    2.431633004235808748e+00, 2.434011129233866644e+00, 2.436391580026358472e+00,
    2.438774358887899840e+00, 2.441159468095329910e+00, 2.443546909927716282e+00,
    2.445936686666354110e+00, 2.448328800594770094e+00, 2.450723253998724260e+00,
    2.453120049166212180e+00, 2.455519188387466745e+00, 2.457920673954961277e+00,
    2.460324508163410417e+00, 2.462730693309773233e+00, 2.465139231693255883e+00,
    2.467550125615311618e+00, 2.469963377379646552e+00, 2.472378989292218332e+00,
    2.474796963661240135e+00, 2.477217302797182441e+00, 2.479640009012775703e+00,
    2.482065084623012119e+00, 2.484492531945147409e+00, 2.486922353298704813e+00,
    2.489354551005475091e+00, 2.491789127389519631e+00, 2.494226084777173114e+00,
    2.496665425497044843e+00, 2.499107151880022748e+00, 2.501551266259272488e+00,
    2.503997770970243231e+00, 2.506446668350667206e+00, 2.508897960740563704e+00,
    2.511351650482239517e+00, 2.513807739920292939e+00, 2.516266231401615538e+00,
    2.518727127275393052e+00, 2.521190429893109819e+00, 2.523656141608549230e+00,
    2.526124264777797279e+00, 2.528594801759243005e+00, 2.531067754913583379e+00,
    2.533543126603823303e+00, 2.536020919195279166e+00, 2.538501135055579727e+00,
    2.540983776554670559e+00, 2.543468846064813604e+00, 2.545956345960592504e+00,
    2.548446278618911709e+00, 2.550938646419000921e+00, 2.553433451742416871e+00,
    2.555930696973045091e+00, 2.558430384497103027e+00, 2.560932516703141371e+00,
    2.563437095982046721e+00, 2.565944124727044251e+00, 2.568453605333699930e+00,
    2.570965540199921850e+00, 2.573479931725964232e+00, 2.575996782314427858e+00,
    2.578516094370263190e+00, 2.581037870300773918e+00, 2.583562112515616516e+00,
    2.586088823426805128e+00, 2.588618005448712456e+00, 2.591149660998072424e+00,
    2.593683792493982843e+00, 2.596220402357906742e+00, 2.598759493013676369e+00,
    2.601301066887493185e+00, 2.603845126407932309e+00, 2.606391674005943848e+00,
    2.608940712114855121e+00, 2.611492243170373762e+00, 2.614046269610588613e+00,
    2.616602793875974164e+00, 2.619161818409390996e+00, 2.621723345656088444e+00,
    2.624287378063707266e+00, 2.626853918082283634e+00, 2.629422968164247365e+00,
    2.631994530764428575e+00, 2.634568608340057683e+00, 2.637145203350768075e+00,
    2.639724318258598323e+00, 2.642305955527996186e+00, 2.644890117625817716e+00,
    2.647476807021333478e+00, 2.650066026186227663e+00, 2.652657777594602084e+00,
    2.655252063722977951e+00, 2.657848887050299869e+00, 2.660448250057934949e+00,
    2.663050155229678140e+00, 2.665654605051753112e+00, 2.668261602012815370e+00,
    2.670871148603954914e+00, 2.673483247318696243e+00, 2.676097900653003681e+00,
    2.678715111105283153e+00, 2.681334881176383078e+00, 2.683957213369597472e+00,
    2.686582110190669503e+00, 2.689209574147792381e+00, 2.691839607751612018e+00,
    2.694472213515231029e+00, 2.697107393954207843e+00, 2.699745151586563363e+00,
    2.702385488932778745e+00, 2.705028408515801619e+00, 2.707673912861047416e+00,
    2.710322004496400261e+00, 2.712972685952216967e+00, 2.715625959761328811e+00,
    2.718281828459045091e+00
};

template<typename Scalar>
static inline Scalar fast_exp(Scalar x) {
    if (x < 0)
        return 1/fast_exp(-x);

    if (x > 100)
        return std::exp(x);

    int cnt = 0;
    while (x >= 1) {
        x = x/2;
        cnt++;
    }

    x = exp_lut[static_cast<int>(x*1024)];

    while (cnt-- > 0) {
        x *= x;
    }

    return x;
}


/**
 * @brief This function is used for the calculation of the digamma function,
 * which is the logarithmic derivative of the Gamma Function. The digamma
 * function is computable via Taylor approximations (Abramowitz and Stegun,
 * 1970)
**/
template <typename Scalar>
static inline Scalar digamma(Scalar x) {
    Scalar result = 0, xx, xx2, xx4;

    for (; x < 7; ++x) {
        result -= 1/x;
    }
    x -= 1.0/2.0;
    xx = 1.0/x;
    xx2 = xx*xx;
    xx4 = xx2*xx2;
    result += std::log(x)+(1./24.)*xx2-(7.0/960.0)*xx4+(31.0/8064.0)*xx4*xx2-(127.0/30720.0)*xx4*xx4;

    return result;
}


template <typename Scalar>
struct CwiseDigamma
{
    const Scalar operator()(const Scalar &x) const {
        return digamma(x);
    }
};


template <typename Scalar>
struct CwiseLgamma
{
    const Scalar operator()(const Scalar &x) const {
        return std::lgamma(x);
    }
};

template <typename Scalar>
struct CwiseFastExp
{
    const Scalar operator()(const Scalar &x) const {
        return fast_exp(x);
    }
};

template <typename Scalar>
struct CwiseIsNaN
{
    const bool operator()(const Scalar &x) const {
        return std::isnan(x);
    }
};

template <typename Scalar>
struct CwiseIsInf
{
    const bool operator()(const Scalar &x) const {
        return std::isinf(x);
    }
};

template <typename Scalar>
struct CwiseScalarDivideByMatrix
{
    CwiseScalarDivideByMatrix(Scalar y) : y_(y) {}

    const Scalar operator()(const Scalar &x) const {
        if (x != 0)
            return y_ / x;
        return 0;
    }

    Scalar y_;
};


/**
 * Reshape a matrix into a vector by copying the matrix into the vector in a
 * way to avoid errors by Eigen expressions.
 */
template <typename Scalar>
void reshape_into(
    const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> &src,
    Eigen::Matrix<Scalar, Eigen::Dynamic, 1> &dst
) {
    size_t srcR = src.rows();
    size_t srcC = src.cols();

    for (int c=0; c<srcC; c++) {
        dst.segment(c*srcR, srcR) = src.col(c);
    }
}


/**
 * Reshape a vector into a matrix by copying the vector into the matrix in a
 * way to avoid errors by Eigen expressions.
 */
template <typename Scalar>
void reshape_into(
    const Eigen::Matrix<Scalar, Eigen::Dynamic, 1> &src,
    Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> &dst
) {
    size_t dstR = dst.rows();
    size_t dstC = dst.cols();

    for (int c=0; c<dstC; c++) {
        dst.col(c) = src.segment(c*dstR, dstR);
    }
}


/**
 * Normalize in place a matrix of row vectors so that they sum to 1. Avoid NaN
 * by checking for 0 explicitly.
 */
template <typename Derived>
void normalize_rows(Eigen::DenseBase<Derived> &x) {
    typename Eigen::DenseBase<Derived>::Scalar s;
    for (int i=0; i<x.rows(); i++) {
        s = x.row(i).sum();
        if (s != 0) {
            x.row(i).array() /= s;
        }
    }
}


/**
 * Normalize in place a matrix of column vectors so that they sum to 1. Avoid
 * NaN by checking for 0 explicitly.
 */
template <typename Derived>
void normalize_cols(Eigen::DenseBase<Derived> &x) {
    typename Eigen::DenseBase<Derived>::Scalar s;
    for (int i=0; i<x.cols(); i++) {
        s = x.col(i).sum();
        if (s != 0) {
            x.col(i).array() /= s;
        }
    }
}


/**
 * Compute the product ignoring zeros.
 */
template <typename Derived>
typename Eigen::DenseBase<Derived>::Scalar product_of_nonzeros(
    const Eigen::DenseBase<Derived> &x
) {
    typename Eigen::DenseBase<Derived>::Scalar p = 1;

    for (int j=0; j<x.cols(); j++) {
        for (int i=0; i<x.rows(); i++) {
            if (x(i, j) != 0)
                p *= x(i, j);
        }
    }

    return p;
}

/**
 * Sum the rows scaled by another vector
 */
template <typename Derived1, typename Derived2, typename Derived3>
void sum_rows_scaled(
    const Eigen::MatrixBase<Derived1> & x,
    const Eigen::MatrixBase<Derived2> & y,
    Eigen::MatrixBase<Derived3> & result
) {
    for (int i=0; i<x.rows(); i++) {
        // this is done so that the multiplication can never result in NaN
        if (y[i] == 0)
            continue;

        result += y[i] * x.row(i);
    }
}

/**
 * Sum the cols scaled by another vector
 */
template <typename Derived1, typename Derived2, typename Derived3>
void sum_cols_scaled(
    const Eigen::MatrixBase<Derived1> & x,
    const Eigen::MatrixBase<Derived2> & y,
    Eigen::MatrixBase<Derived3> & result
) {
    for (int i=0; i<x.cols(); i++) {
        // this is done so that the multiplication can never result in NaN
        if (y[i] == 0)
            continue;

        result += y[i] * x.col(i);
    }
}

/**
 * Wrap a PRNG with this class in order to be able to pass it around even
 * to other threads and protect its internal state from being corrupted.
 *
 * see UniformRandomBitGenerator C++ concept
 * http://en.cppreference.com/w/cpp/concept/UniformRandomBitGenerator
 */
template <typename PRNG>
class ThreadSafePRNG
{
    public:
        typedef typename PRNG::result_type result_type;
        static result_type min() { return PRNG::min(); }
        static result_type max() { return PRNG::max(); }

        ThreadSafePRNG(int random_state) {
            prng_mutex_ = std::make_shared<std::mutex>();
            prng_ = std::make_shared<PRNG>(random_state);
        }

        result_type operator()() {
            std::lock_guard<std::mutex> lock(*prng_mutex_);

            return (*prng_)();
        }

    private:
        std::shared_ptr<std::mutex> prng_mutex_;
        std::shared_ptr<PRNG> prng_;
};


}  // namespace math_utils
}  // namespace ldaplusplus

#endif // UTILS_H