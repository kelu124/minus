This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
|     |         | IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026 |     |        |     |        |            |     |              |            |     |     |     |     | 1   |
| --- | ------- | --------------------------------------------- | --- | ------ | --- | ------ | ---------- | --- | ------------ | ---------- | --- | --- | --- | --- | --- |
|     | Current |                                               |     | Trends |     | in     | Ultrasound |     |              | Wearables: |     |     |     |     |     |
|     |         | Spotlight                                     |     |        | on  | System |            |     | Architecture |            |     |     |     |     |     |
David Weik , Member, IEEE, Richard Nauber , Senior Member, IEEE, Erik Kaiser ,
Nele Kirsch , Graduate Student Member, IEEE, Robert Kunz , Lennart Schierling ,
Christoph Leitner , Member, IEEE, Luca Benini , Fellow, IEEE, Hsiao-Chuan Liu , Member, IEEE,
Qifa Zhou , Fellow, IEEE, Jochen Hampe , Gerhard Fettweis , Moritz Herzog , Member, IEEE,
|     |     |     |     |     | and Christian |                 | Kupsch | , Member, | IEEE |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | ------------- | --------------- | ------ | --------- | ---- | --- | --- | --- | --- | --- | --- |
|     |     |     |     |     |               | (Methodological |        | Review)   |      |     |     |     |     |     |     |
Abstract—Wearable ultrasound sensing systems are of hardware and software at the system-level remains a
rapidly emerging for precise, continuous, and intuitive major barrier to mass deployment. This review maps the
biomedical monitoring and human-in-the-loop interaction technology readiness and architectures of wearable ultra-
in healthcare, industry, and rehabilitation. These systems sound systems, and examines critical design trade-offs,
must operate under stringent constraints on size, weight, including edge versus cloud-based processing and pulse-
and power while delivering actionable physiological and echo versus coded signal approaches. We identify recur-
functional information. Advances in micromachined trans- ring design principles and argue that modular, scalable,
ducers, conformable electronics, low-power signal pro- and reusable platforms are key to lowering development
| cessing, | and | edge artificial |     | intelligence | (AI) | have enabled |     |          |                  |     |             |      |            |     |     |
| -------- | --- | --------------- | --- | ------------ | ---- | ------------ | --- | -------- | ---------------- | --- | ----------- | ---- | ---------- | --- | --- |
|          |     |                 |     |              |      |              |     | barriers | and accelerating |     | translation | from | prototypes |     | to  |
thefirstgenerationofwearableprototypes,yetintegration
|     |     |     |     |     |     |     |     | commercial | deployment |     | across | healthcare, | industrial, |     | and |
| --- | --- | --- | --- | --- | --- | --- | --- | ---------- | ---------- | --- | ------ | ----------- | ----------- | --- | --- |
consumerdomains.
Manuscript received 17 October 2025; revised 18 January 2026; Index Terms—Wearable ultrasound, wearable health
accepted 5 February 2026. The work of Richard Nauber, Gerhard monitoring, human-machine interfaces, edge computing,
| Fettweis, | Jochen | Hampe, | and Moritz | Herzog | was | supported | in part |     |     |     |     |     |     |     |     |
| --------- | ------ | ------ | ---------- | ------ | --- | --------- | ------- | --- | --- | --- | --- | --- | --- | --- | --- |
codedsignals,wirelesssystems,systemdesign.
| by the | German | Federal Ministry | of  | Research, | Technology | and | Space |     |     |     |     |     |     |     |     |
| ------ | ------ | ---------------- | --- | --------- | ---------- | --- | ----- | --- | --- | --- | --- | --- | --- | --- | --- |
(BMFTR)underGrant16ME0531andGrant16KISK051andinpartby
EuropeanUnionandtaxrevenuesonthebasisofthebudgetadopted I. INTRODUCTION
| by the | Saxon | State Parliament | under | Grant | 100689694. | The work | of  |     |     |     |     |     |     |     |     |
| ------ | ----- | ---------------- | ----- | ----- | ---------- | -------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
ChristophLeitnerwassupportedbySwissNationalScienceFoundation WEARABLEultrasoundisemergingasakeytechnology
underAmbizioneGrant233457.TheworkofChristianKupschwassup-
tomeetthegrowingdemandforcontinuous,unobtrusive
portedbyDeutscheForschungsgemeinschaft(DFG,GermanResearch
|                                                      |     |     |     |     |     |     |        | physiological | monitoring |     | and human-in-the-loop |     |     | interaction |     |
| ---------------------------------------------------- | --- | --- | --- | --- | --- | --- | ------ | ------------- | ---------- | --- | --------------------- | --- | --- | ----------- | --- |
| Foundation)underProject260366138andProject532905681. |     |     |     |     |     |     | (David |               |            |     |                       |     |     |             |     |
forhealthcare,industry,andrehabilitation[1],[2],[3].Inthese
Weik,RichardNauber,MoritzHerzog,andChristianKupschcontributed
equallytothiswork.)(Correspondingauthor:ChristianKupsch.)
domains,commondriversincludeagingpopulations,theshiftto-
DavidWeik,RobertKunz,LennartSchierling,andChristianKupsch
wardspersonalizedandpreventivemedicine,andtheincreasing
| are with | Measurement, | Sensor | and | Embedded | Systems | Laboratory |     |     |     |     |     |     |     |     |     |
| -------- | ------------ | ------ | --- | -------- | ------- | ---------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
integrationofhumansensingintoadaptivetechnicalsystems.In
(MSELab),TUBergakademieFreiberg,09599Freiberg,Germany(e-
mail:christian.kupsch@mse.tu-freiberg.de). healthcare,thisincludeslongitudinal,non-invasivemonitoring
RichardNauber,NeleKirsch,andGerhardFettweisarewiththeVoda-
|     |     |     |     |     |     |     |     | of physiological | parameters |     | such | as blood | pressure | or  | tissue |
| --- | --- | --- | --- | --- | --- | --- | --- | ---------------- | ---------- | --- | ---- | -------- | -------- | --- | ------ |
foneChairMobileCommunicationsSystems,DepartmentofElectrical
Engineering,TUDresden,01069Dresden,Germany. perfusion in both clinical and home settings [4]. In industry,
Erik Kaiser and Moritz Herzog are with the Else Kröner Fresenius human-in-the-loop interaction integrates human action and
CenterforDigitalHealth,TUDresdenFacultyofMedicineCarlGustav decision-makingintoroboticandaugmented-realitysystems[5],
Carus,01307Dresden,Germany.
Christoph Leitner is with the Department of Information Technology while rehabilitation and personal training increasingly rely on
andElectricalEngineering,ETHZurich,8092Zurich,Switzerland. home-based applications with real-time tracking and adaptive
| Luca | Benini | is with the | Department | of Information |     | Technology | and |     |     |     |     |     |     |     |     |
| ---- | ------ | ----------- | ---------- | -------------- | --- | ---------- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
ElectricalEngineering,ETHZurich,8092Zurich,Switzerland,andalso feedback[6].Together,thesetrendsrequiresensingtechnologies
withtheDepartmentofElectrical,Electronic,andInformationEngineer- thatoperatereliablyoverextendedperiods,adapttoawiderange
ing,UniversityofBologna,40126Bologna,Italy. ofreal-worldconditions,andprovidemeaningfulphysiological
Hsiao-ChuanLiuiswiththeDepartmentofBiomedicalEngineering,
insightinbothsupervisedandunsupervisedenvironments.
UniversityofMassachusettsAmherst,Amherst,MA01002USA.
QifaZhouiswiththeDepartmentofOphthalmologyandBiomedical Among wearable sensing modalities, ultrasound stands out
Engineering,ViterbiSchoolofEngineering,UniversityofSouthernCali-
|     |     |     |     |     |     |     |     | by combining | diagnostic |     | depth, | tissue specificity, |     | and | safety |
| --- | --- | --- | --- | --- | --- | --- | --- | ------------ | ---------- | --- | ------ | ------------------- | --- | --- | ------ |
fornia,LosAngeles,CA90007USA.
|     |     |     |     |     |     |     |     | with the | potential | for continuous |     | operation. | While | a range | of  |
| --- | --- | --- | --- | --- | --- | --- | --- | -------- | --------- | -------------- | --- | ---------- | ----- | ------- | --- |
JochenHampeiswiththeMedicalDepartment1,UniversityHospital
alternativemodalitiesisactivelyexplored[7],[8],[9],[10],few
| Dresden, | TU  | Dresden Faculty | of  | Medicine | Carl Gustav | Carus, | 01307 |     |     |     |     |     |     |     |     |
| -------- | --- | --------------- | --- | -------- | ----------- | ------ | ----- | --- | --- | --- | --- | --- | --- | --- | --- |
Dresden,Germany.
|      |         |                   |     |              |          |           |     | offer comparable |           | access | to hemodynamic |      | and structural |     | infor- |
| ---- | ------- | ----------------- | --- | ------------ | -------- | --------- | --- | ---------------- | --------- | ------ | -------------- | ---- | -------------- | --- | ------ |
| This | article | has supplementary |     | downloadable | material | available | at  |                  |           |        |                |      |                |     |        |
|      |         |                   |     |              |          |           |     | mation while     | remaining |        | compatible     | with | non-invasive,  |     | body-  |
https://doi.org/10.1109/RBME.2026.3664011,providedbytheauthors.
conformaldeployment.Significantly,therealizationofwearable
DigitalObjectIdentifier10.1109/RBME.2026.3664011
©2026TheAuthors.ThisworkislicensedunderaCreativeCommonsAttribution4.0License.Formoreinformation,see
http://creativecommons.org/licenses/by/4.0/

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
2 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
Fig. 1. Overview of wearable ultrasound systems across application domains and their requirements. Present R&D emphasizes application-
specific systems, while shared platforms (vision) based on common design rules and directions could accelerate early-stage development but
remainunavailableorataveryearlystage.
ultrasoundsystemshasonlyrecentlybecomefeasible,enabled meettherequirementsalltogetherhavesofarreceivedlimited
byrapidadvancesinsupportingtechnologies: attention.Givenitsimportanceforapplicationdevelopmentand
(cid:2)
Novel micromachined ultrasound transducers now offer commercialization,thisraisestwocentralquestionsthatframe
low-cost,wafer-scalefabrication[11],[12],[13], ourreview.
(cid:2)
Flexible,conformableelectronicsubstratesnowallowul- First,whichdesignstrategiesbestaddresstheconstraintsof
trasound sensors [14] and circuitry [15] to adapt to the wearability, and what factors determine the transition of ultra-
body’ssurface[16], soundsystemsfromprototypestocommercialproducts?Tran-
(cid:2)
Highly integrated and energy-efficient signal process- sitioningwearableultrasoundsystemsfromresearchprototypes
ingarchitecturessupportcontinuousoperationwithinthe towidelyadoptedtoolsinhealthcare,industry,orpersonaluse
strict power constraints of wearable systems [17], [18], requirestechnicalfeasibility,butalsoeconomicviability.Forex-
[19],[20],and ample,theminiaturizationofultrasoundhardwareoftendepends
(cid:2)
Embedded artificial intelligence processors and algo- on custom silicon integration [20], which demands substantial
rithmsallowon-deviceinferenceandreal-timedecision- upfrontinvestments,onlyjustifiediflarge-scaledeploymentis
making[21],[22]. foreseeable.Inthisreview,weexaminethisinvestmentthreshold
Together,theseadvancesestablishthetechnologicalfounda- by assessing the potential market size alongside the current
tionforwearableultrasoundapplications,(seeFig.1). development status of wearable ultrasound applications with
Wearableultrasoundsystemsinheritmanyofthecoredesign their respective technology readiness levels (TRL). We aim to
requirements found in clinical [23], [24] and portable [25], highlight the application domains that would benefit the most
[26], [27] scanners. These include generating and acquiring fromnear-termsystem-levelinnovationofultrasoundwearables
ultrasoundsignalsacrosschannelcountsrangingfromonlyafew and examine how common architectural and design strategies
single-elementstohundredsoreventhousandsinarraysystems, mayaccelerateadoption.
incombinationwiththeneedforreal-timeprocessingforsignal Second,howdocurrentimplementationsaddressmodularity,
analysis,imaging,andinformationextraction[28].Inaddition, reuse,andscalabilityindesign?Currentresearchshowsthatthe
all ultrasound systems require bio-compatible packaging and developmentofwearableultrasoundsystemsremainshighlyad
must comply with safety regulations regarding thermal and hoc:mostprototypesareapplication-specific,withcustomhard-
acousticexposure[29]. wareandsoftwaretailoredtoasingleusecase[35],[36],[37].
In wearable systems, these requirements are complemented Whilethisallowsfordeepoptimization,itleadstofragmented
by additional considerations on weight, runtime, unsupervised solutions,witheachprojectrequiringseparatetransducerinter-
reliability, latency, and form factor [30], which considerably faces,acquisitioncircuitry,andprocessingpipelines.Asaresult,
restrict the design space (see Fig. 1). Towards deployment, eachnewprojectoftenrequiresbuildingupcoresystemcompo-
manyreviewsonwearableultrasoundhaveaddressedadvances nentsfromscratch[15],[38],raisingthebarrierforinterdisci-
in transducer materials, novel application domains or clinical plinaryteamstopursueapplication-levelresearch.Incontrast,
translation[1],[2],[3],[16],[29],[31],[32],[33],[34].System- modular and reusable platforms could accelerate development
level considerations on how to combine these advances and acrossapplicationdomains,astheytakedevelopmentoverhead

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 3
from interdisciplinary groups and enable them to focus on in- TRL.FurtherdetailsoftheTRLassessmentaregiveninthesup-
novationratherthanhardwareintegration.Suchplatformscould plementSection1.Anoverviewofthedifferentusecases,their
lowerthebarriertoentryforapplication-orientedresearchers,in- TRLassessment,andtheircommercialpotentialisprovidedin
cludingclinicians,rehabilitationscientists,orHMIdevelopers, Fig.2.
whowishtoexplore wearable ultrasound butlackexpertisein
hardwaredesign.Bydecouplingsystem-levelengineeringfrom
domain-specificinnovation,modularplatformsshortendevelop-
A. MedicalMonitoring
ment cycles, accelerate prototyping, and broaden participation
acrossdisciplines,asdemonstratedbystationaryultrasoundre- Themostprominentandimpactfulapplicationsofwearable
searchplatforms[39],[40],[41],[42].Ourgoalistoanalyzethe ultrasound are probably within the medical field, with sys-
system-levellandscape ofultrasound wearables byidentifying tems being developed for continuous health monitoring, diag-
recurring architectural patterns, modular design elements, and nostics, and disease treatment [30]. Wearable medical devices
pointsofvariabilitythatcouldconvergeintocommonplatforms substantially support the early detection, as well as long-term
(seeFig.1). monitoring of various diseases. They enable continuous and
This review does not propose a specific platform design; context-awareacquisitionofphysiologicalparameters,notonly
rather, it provides a structured synthesis to inform discussions within, but also outside of clinical settings [31]. This ex-
about shared components and potential convergence. It sur- tends diagnostic capabilities beyond sporadic in-clinic mea-
veysdevelopmentspublishedfrom2018tomid-2025,drawing surements and facilitates more informed medical decisions. In
on academic literature, patents, technical documentation, and addition, such systems contribute to the relief of healthcare
publicinformationoncommercialproducts.Bycombiningin- infrastructures, promote health awareness and patient empow-
sightsfromresearchandindustry,thisreviewaimsforaninte- ermentthroughincreasedpersonalinvolvementindiseaseman-
gratedoverviewofsystem-levelarchitecturesandtheiremerging agement [29]. The market for medical wearables is expected
applications. The scope is limited to sensing applications of to exceed $3.7 billion by 2030, with a Compound Annual
wearableultrasoundandexcludestherapeuticuses,duetotheir GrowthRate(CAGR)of8.2% [44],seeFig.2(a).Ultrasound-
fundamentally different system requirements. We first analyze basedsolutionsareconsideredasignificantcontributiontothis
potentialapplicationdomainsintermsofmarketrelevanceand growth due to their non-invasive nature and high diagnostic
current TRL (Section II). We then outline the fundamental accuracy.
design principles and building blocks of ultrasound systems, Inthefieldofcontinuoushealthmonitoring,bloodpressure
emphasizing aspects particularly relevant to wearable imple- monitoring plays a pivotal role [45]. In clinical practice, this
mentations (Section III), before reviewing the state-of-the-art parameter is essential for assessing patient status and is ob-
in key trends, implementations, and system concepts (Section tained either invasively, with associated infection risk, or non-
IV). Finally, we synthesize the findings by linking specific invasively,yieldingonlyintermittentmeasurements.Topursue
applicationstoarchitecturaldemandsandmarketpotential,and acontinuousandnon-invasivebloodpressuremonitoring,[46]
identify cross-domain opportunities and promising directions evaluated sequential ultrasound pulses in the forearm or the
forfutureresearch(SectionV). carotid artery with a wearable system. The method was val-
idated in various clinical settings on human subjects, includ-
ing outpatient evaluations of postural homeostasis, the cardiac
catheterizationlaboratory,andtheintensivecareunit.Therefore,
II. FORTHCOMINGAPPLICATIONSANDMARKETPOTENTIAL
thetechnology can be classifiedas TRL 7.To furtheradvance
The following section aims to provide a comprehensive the research system used, the group also demonstrated a fully
overview of technological maturity, commercial potential, and wearabledeviceinacomplementarystudy[15].
application-specific trends as a contextual groundwork to the Bloodflowvelocityisalsoacrucialparameterforcontinuous
system architecture of ultrasound wearables. Therefore, we cardiovascularhealthmonitoring.Bloodflowvelocitydescribes
categorized the landscape of wearable ultrasound applications the speed at which blood travels through the arteries, with
into three main domains: (1) Medical monitoring, (2) human- deviations that may indicate cardiovascular disorders such as
machineinterfaces(HMI),and(3)monitoringforrehabilitation, stenosis or heart failure. Ref. [47], [48] showed that wearable
sports and lifestyle. For each sector, we analyze the market Doppler ultrasound can reliably measure blood flow velocity,
size and the compound annual growth rate (CAGR) to judge forwhich[35]commercializedFloPatchforreal-timehemody-
commercial potential. Specific use cases and functional areas namic monitoring. FloPatch has been validated in operational
are assessed by evaluating their current stage of development settings and is ready for large-scale deployment and manufac-
using Technology Readiness Levels (TRL) [43]. The TRL as- turing,correspondingtoTRL8.
sessment primarily reflects the degree of application-specific Furthermore,ultrasoundenablesthemeasurementofbothres-
validation, with emphasis on the extent to which the intended piratoryrateandtidalvolume.Together,theseparameterseval-
functionality has been demonstrated in relevant environments. uate whether respiration provides adequate ventilation, which
Accordingly, the assessment is not limited to fully wearable is particularly important after extubation and in postoperative
solutions.Instead,evenstationarysolutionswiththefuturegoal or otherwise vulnerable patients, where reliable, noninvasive
ofawearableapplicationareincludedanddenotedbyalower tidal-volume monitoring remains unavailable. Respiratory rate

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
4 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
Fig. 2. Total wearable market and application fields of wearable ultrasound technologies. (a), total wearable market volume and expected
growth[44],includingthecontributionofultrasoundwearables,subdividedintomedical,industrialandconsumermarkets.(b),Currentstatusof
ultrasoundwearableapplicationsbytechnologyreadinesslevel(TRL),groupedbyapplicationdomainsfromasystem-architectureperspective.The
classificationschemediffersfromthatina:Whilemarketdatawastypicallyreportedformedical,industrial,andconsumerdomains,system-level
considerations were better reflected by medical monitoring, human–machine interfaces, and rehabilitation, sports, and lifestyle applications.
Additionallyforeachdomain,themedianTRLisdepictedasahorizontallineinthecorrespondingcolor.
isalreadymonitoredforexamplethroughpulseoximetry,ECG- TRL is assessed as level 4, as validation was limited to phan-
based impedance measurements, or simple manual counting. tomsapproximatingrelevanttissueproperties.Fromahardware
For both, respiratory rate and tidal volume, [15] demonstrated perspective,thesystemsofarremainswire-connectedtoexternal
a wearable ultrasound-based system with a correlation greater devicesandisnotfullywearable.
than 99% between diaphragmatic displacement and tidal vol- Continuous monitoring of cerebral blood flow and
ume. Although the system of [15] is highly advanced and hemodynamics is crucial for detecting early cerebrovascular
the application has been demonstrated on human subjects, de- dysfunctionsandvascularpathologies,whilealsoenablingthe
ployment in an operational environment is still pending. The assessmentofneurovascularfunctionsrelatedtosensory,motor,
application-specificTRListhereforeclassifiedaslevel6. and cognitive processes [29]. After the early proof-of-concept
Toenabledirectassessmentofadditionalcardiovascularpa- study by [55], [56] demonstrated a conformable ultrasound
rameters,[49]developedasoftultrasoundpatchforcontinuous path for stable long-term coupling and volumetric transcranial
cardiacimaging,providingreal-timemonitoringofstrokevol- Doppler imaging towards real-time assessment of intracranial
ume, cardiac output, and ejection fraction. It qualifies as TRL hemodynamics. Given the demonstrated functionality
6,asitsfunctionalityhasbeendemonstratedonmultiplehuman of the patch in multiple human subjects, but pending
subjects, while clinical validation is still pending. So far, the validation in routine clinical use, the TRL is assessed as
systemreliesonawiredconnectiontolargerexternaldevices. Level6.
Towardsdeployment,SonusMicrosystemsandPulsifyMedical Afurtherapplicationpresentedby[57]integratesultrasound
arebothdeveloping cardiacultrasoundpatches,withthelatter imaging and low-intensity focused neuromodulation by em-
alreadydemonstratingsuccessfulimaging[50],[51].Atthetime ploying two dedicated transducer arrays. Such neuromodula-
ofwritingthisreview,neitherdeviceiscommerciallyavailable. tion approaches aim to modulate the firing rates and patterns
In prenatal care, continuous fetal heart rate monitoring of peripheral nerves, thereby enabling controlled activation of
supports early detection of hypoxic events and thereby aiding downstreammusculatureandofferingtherapeuticrelevancefor
timely intervention, particularly in high-risk pregnancies. For conditions such as overactive bladder, neuropathic pain, and
thispurpose,GEHealthCareintroducedthefullyportablewire- disorders related to the vagus nerve. Although this review fo-
less system Novii+ [52], which reaches TRL 9 as it is already cussesonmonitoringapplications,theworkof[57]isconsidered
commerciallyavailable. here due to its combined use of ultrasonic sensing and mod-
In postoperative tumor management, early detection of re- ulation. Since neuromodulation was demonstrated exclusively
currence is crucial [53]. Ultrasound enables more continuous, on an in-vitro active phantom emulating peripheral nerve and
radiation-free monitoring compared to intermittent ionizing muscle responses, without validation in human subjects, the
imagingmodalities.Ref.[54]developedasystemthatenables system is classified as TRL 4. The current prototype remains
long-term monitoring of brain tumor growth after surgery by wire-connectedtoexternalhardwareandwasthereforenotyet
integrating ultrasound technology into a cranial implant. The realizedasafullywearableplatform.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 5
Timely detection of acute liver failure is of critical clinical making it particularly advantageous for gesture decoding, dis-
importance,particularlyfollowingorgantransplantationorpost- creteforceclassification,andotherfine-grainedmotortasksin
operativeintensivecare.Earlyidentificationfacilitatestargeted noisyordynamicconditions[64].Becauseitssignalcharacter-
therapeutic interventions, markedly decreasing consequential isticsareinherentlyrobusttoambientelectromagneticnoiseand
damage and mortality. In this field, [58] presented a wearable reflect mechanical rather than electrical muscle activity, ultra-
ultrasoundsystemcapableofcontinuouslymeasuringliverstiff- soundcaneitherserveasastandalonemodalityorcomplement
ness via ultrasonic shear wave elastography. As validation has sEMGbyaddingdeformation-basedinformationthatenhances
beenlimitedtoanimalmodels,thesystemcurrentlyqualifiesas overall reliability in multimodal HMI systems. Additionally,
TRL4.Moreover,thesystemsofarreliesonwiredconnections, ultrasound is also enhancing eye-tracking capabilities due to
necessitatingafuturesystemdesignforawearableintegration. itsrobustnessagainstambientlightinterference[65].Basedon
Long-term imaging of inner organs can provide clinically theseadvantages,ultrasound-basedgestureandeyerecognition
relevantinformationonpostoperativerecovery,internalinjuries, systemsarebecomingincreasinglyprevalentinbothconsumer
orcomplicationswithoutrequiringrepeatedhospital-basedex- electronics and industrial environments. The market size for
aminations.Toaddressthisneed,[11]introducedabioadhesive industrialwearablesisexpectedtoreach$26millionby2030,
piezoelectricultrasoundarraydesignedforcomfortable48-hour driven by a CAGR of 10% , with HMI applications playing a
wearandcapableofstableimagingunderdynamicconditions. particularlysignificantrole[44].
Whilethesystemenablescontinuousacquisitionofhigh-quality In 2024, [66] introduced an ultrasonic wristband for three-
imagesonthebody,itremainstetheredtoanexternalVerasonics dimensional pointer control, achieving markedly higher wrist-
Vantage system for data acquisition, and all recorded images angle prediction accuracy than sEMG. Ref. [67] demonstrated
requiremanualevaluationbyclinicians.Giventhattheimaging motionintentdecodingfromunlabeledultrasoundsignalswith
modalityhasbeendemonstratedonhumansubjectsinrealistic a self-supervised deep learning method, which was validated
environments,theTRLisassessedaslevel6. withtenprobandsincludingonetransradialamputee.Toenhance
For theearlydetection ofpneumothorax (PTX),[59]devel- robustness,[68]alsointroducedamultimodalwearablesystem
opedasystemcapableofdetectingtheabsenceoflungsliding. integratingsEMG,inertialsensors,andA-modeultrasound.
Earlyidentificationandcontinuousmonitoringofpneumothorax Focusingonenergyefficiency,[69],[70]demonstratedfeature
areclinicallyessential,asprogressioncanoccurrapidlyandmay extractionandthree-dimensionalpointercontrolonafullywear-
leadtosevererespiratorycompromise,hemodynamicinstability, able low-power ultrasound system. Expanding beyond gesture
and the need for immediate intervention. The approach is cur- recognition, [71] incorporated grip-force estimation, and [72]
rentlyatTRL3.Furtherstepstowardsahigherlevelwillneed improved robustness to forearm-position variations through a
a quantitative validation of the results and a wearable system position-invariantalgorithm.
integration. Overall, the TRL for gesture recognition applications based
Ref. [60] developed a wearable ultrasound patch designed on muscle activity tracking is classified as Level 6, as the
for integration into a bra for breast cancer monitoring and applications have already been validated on human subjects,
early detection. Initial in vivo validation in a human subject whilevalidationinanoperationalenvironmentisstillpending.
demonstratedthefeasibility.Sincethetechnologyhasonlybeen Eyetrackingplaysacriticalroleinenablinguserinteraction
demonstratedonasinglehumansubjectratherthaninabroader withinARandVRgoggles.However,opticaltrackingmethods
operational setting, the current TRL is classified as level 5. face substantial challenges in non-sealed headset designs due
In the current system, data transmission and power supply are to the influence of ambient light, which is compromising the
externallywired,showingfurtherpotentialtowardsthesystem’s functionality [65]. To address this limitation, [65] presented a
autonomy. laboratorydemonstratoratFacebookRealityLabs,showcasing
For urinary bladder monitoring, the primary objective is to anultrasound-basedapproachforgazeestimation.Intheirsetup,
enhancethequalityoflifeforindividualsaffectedbyurinaryin- static gaze angles were simulated using a physical model eye.
continence[61].Ref.[62]and[63]recentlyintroducedsystems Given that the system was only validated in a non-wearable
employing wearable ultrasound. As systems are commercially laboratorysetupusingamodeleye,andneitherintegratedinto
available,theTRLisat9. anactualheadsetnortestedonhumansubjects,itstechnology
readinesslevel(TRL)iscurrentlyassessedaslevel4.
B. Human-MachineInterfaces
C. MonitoringforRehabilitation,SportsandLifestyle
Wearable ultrasound technology is increasingly relevant for
HMI, offering competitive gesture recognition accuracy com- Wearable devices such as smartwatches, smart rings, and
pared to surface electromyography (sEMG) by precisely cap- fitness bands are increasingly used in daily life to monitor
turingandlocalizingmusclemovementsthroughmorphological individualwell-beingthroughparameterssuchassleepquality,
changes[30],[64].IncontrasttosEMG,whichaffectedbyskin heartratevariability,andbloodoxygensaturation[8].Theglobal
impedance,electrodeshifts,andelectromagneticnoise,A-mode marketforconsumerdevicesisexpectedtosurpass$4.4billion
ultrasoundcapturesmusclemorphologydirectly,providingsta- by2030,withaCAGRof8.8% [44].Alsointhisfield,agrowing
ble features even under varying contraction levels. Ultrasound marketshareforultrasonicwearablesisforeseeable,drivenby
signalsenablereliablerecognitionofdeepmusclemovements, theirabilitytocapturebiomechanicalinformation.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
6 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
Buildingonthisgrowingroleinpersonalhealthmonitoring, Ref.[76]developedandvalidatedawearablesystemcombin-
wearable systems are progressively being developed to sup- ingultrasound,EMG,andMMGtomonitorgait-relatedmuscle
port the early detection of diseases, thereby enabling timely activityinstrokesurvivors.Thesystemenablesobjectivetrack-
diagnosisandintervention.Althoughthesedevicestargetphys- ingofrehabilitationprogress,supportsearlydetectionofcom-
iological parameters similar to those monitored by clinically pensatory movement patterns, and informs timely adjustment
deployedmedicalsystems,theyareprimarilyusedinpreventive of individualized treatment plans. As the technology has been
or lifestyle-oriented contexts rather than in clinical care. This successfullytestedonpatientsubjectsduringnaturalmovement,
convergenceinmeasurementtargetsiscontrastedbydivergent itisclassifiedasTRL6.
design priorities: Lifestyle wearables are heavily constrained Beyondtrainingoptimizationforrehabilitationorsportpur-
by size, weight, and usability requirements, and often aim to poses, ultrasound has been employed to assess the contractile
extractmultiplephysiologicalparametersfromcompactsensor propertiesofskeletalmuscleforinjurypreventionandrecovery
modules. Such multifunctionality typically comes at the cost monitoring[77].Thisincludescontractionthickness,duration,
ofreducedmeasurementaccuracy.Inclinicalenvironments,by velocity, maintenance, and half-relaxation time. The experi-
contrast, these constraints are less stringent, allowing the use mental proof of concept in laboratory by [77] demonstrated a
of dedicated and validated measurement modalities that offer TRL3forthisapproach.Ref.[78]demonstratedmusclefatigue
higher accuracy and robustness. As a result of these converg- detection using ultrasound in a laboratory environment. With
ing measurement targets and diverging design priorities, the thiswork,theauthorsshowcaseaTRL4forfatiguedetection,
boundarybetweenlifestyleandmedicalapplicationshasbecome as the approach was validated only in controlled laboratory
increasingly difficult to draw and often depends solely on the experimentswithoutapplicationinarelevantenvironment.Both
presenceofofficialmedicalcertification. systemsarestillconnectedtoexternaldevicesviacables.
Beyond health-related self-monitoring, wearables also play
an expanding role in rehabilitation and sports. These systems
D. Implications
enable real-time tracking and recording of physical activity
andrelevantphysiologicalparameters,therebyfacilitatingdata- Ultrasound-based wearables show a wide range of applica-
driventrainingoptimization.Withthegrowingadoptionofsuch tionsthroughoutvariousfields.Althoughmarketfiguresspecif-
technologies across the general population, advancements in icallyforultrasound-basedwearableshavenotyetbeenreliably
measurement accuracy or the integration of additional physio- reported, their potential is underscored by the overall growth
logicalparametersholdthepotentialtoexertasubstantialimpact of the wearable market, which is estimated to expand into the
onpublichealth. multi-billion-dollar range with a CAGR above 8% . This sug-
Blood pressure as a key cardiovascular parameter discussed gestsafavorablemarketenvironmentfornovelultrasound-based
inSectionII-Aisalsorelevantforhealthtracking[46].Further applications. However, only a limited number of commercial
relevant adoptions from medical monitoring involve the early devicesarecurrentlyavailable.
detectionofconditionssuchasbreastcancerandpneumothorax, Our TRL assessment across different domains reveals sub-
orthemonitoringofrespiratoryrateandtidalvolume,withthe stantialvariabilityinthematurityofultrasoundwearabletech-
latterenablingnovelinsightsintobreathingefficiency,training nologies. While some use cases in medical monitoring, such
loadandrecoveryinlifestyleandprofessionalsports.TheTRL as bladder state assessment, fetal heart-rate monitoring, and
for these applications is assessed similarly to their medical blood-flowvelocityestimation,haveprogressedtocommercial
counterparts, as they rely on the same underlying measurable products, many applications remain at the research stage with
quantities. initialpilotstudiesandlaboratoryprototypes.Evenindomains
Ref. [73] developed an algorithm capable of estimating the whereadvancedTRLshavebeenreachedthroughvalidationin
pennation angle without image reconstruction. The pennation relevant environments, the underlying ultrasound systems are
angle is a relevant parameter for estimating maximum mus- rarely fully wearable. Instead, they remain tethered to large,
cle force depending on the training status. This technique is high-performance, and power-intensive backend systems such
currently classified as TRL 3, as only an experimental proof astheVerasonicsVantageplatformandworkstation-classcom-
of concept has been demonstrated in the laboratory. Detection puters.Ultrasoundwearablesinthedomainofhuman-machine
of muscle activity can also enable the adaptive application of interfacestypicallyresideatTRL4to6,supportedbyconvincing
spatiallydistributedsequentialstimulation(SDSS),whichwas laboratory demonstrations but limited by challenges in weara-
shown by [74] to reduce muscle fatigue (MF). The authors bility,semanticinference,andsystemintegration.Applications
demonstrated TRL 3 of this approach, with the potential to inlifestyle,rehabilitation,andprofessionalsportsalsoremainat
target further technological validations in the future. Ref. [75] earlyTRL3to7,whereproof-of-conceptresultsexist,butvali-
presentedasystemforpredictinggroundreactionforcesduring dationinrelevantenvironments,manufacturability,andmarket
isometric squats in a laboratory setting, which is assessed at fitremainuncertain.
TRL5.Theseworksdemonstratethatultrasoundcanbeusedto Concluding all three domains, we identified five common
accuratelymonitormuscleactivity,allowingforoptimizationof challengesthatmainlyhinderfurtherTRLadvancementsofthe
movementpatternsandindividualizationoftrainingprotocols. proposedapplications:
(cid:2)
Yet,neitherofthesesystemsisavailablefullywearable,asthey System-level integration to meet requirements for wear-
aresofaroperatewithwiredperipheralcomponents. ableapplications,

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 7
(cid:2)
Fragmentedsolutionsandthenecessityforcustom-build size,makingsuchsystemsparticularlywell-suitedforwearable
solutionsraiseentrybarriers, applications, albeit at the cost of reduced temporal resolution.
(cid:2)
Regulatoryandsafetyconstraintsforwearableultrasound Envelopedetectionandlog-compressionofthereceivedsignals
devices[29], produce amplitude mode (A-mode) profiles, depicting reflec-
(cid:2)
Reliableandautonomouson-bodyoperation, tivity over time or depth (see Fig. 3(e)). Building on A-mode
(cid:2)
Manufacturabilityandeconomicprofitability. data,repeatedlyacquiringsignalsfromasinglereceivechannel
Theseconsiderationsaretightlycoupledtosystemarchitec- over time produces a motion mode (M-mode) representation,
tureandthetrade-offsinvolved,forinstancebetweenembedded which enables visualization and analysis of motion within the
computation, wireless communication, and energy consump- scanned object [79]. Similarly, a set of coherent echo profiles
tion. Insights from early commercial successes in handheld allows to measure flow velocities along the direction of the
ultrasound further highlight that a focused use case, strong ultrasonicbeambyevaluatingtheDopplershift[79].Toachieve
systemintegration,clearregulatorypositioning,andrelianceon a higher level of information retrieval, see Fig. 3(f), further
commoditycomputeplatformscanacceleratetranslation;prin- advancedmethodsofprocessinginvolvephaseevaluation[15],
ciplesthatwilllikelygeneralizetowearableultrasoundaswell. spectroscopy [38], feature extraction [80] and neural network
Therefore,ratherthanconceptuallimitationsoftheapplications, processing[69].
system-levelconstraintsarethedominantbottleneckstohigher Imagingsystemsadditionallyinvolvethecrucialprocessing
TRLs.Powerconsumption,safetycompliance,autonomousre- partofimagereconstruction(seeFig.3(d)).Thismeans,thatthey
liability, and manufacturability challenge all application areas captureinformationcoherentlyalongatleasttwospatialdimen-
alike.Thissharedtechnologicalburdenhighlightstheneedfora sions,incontrasttonon-imagingsystemswhichonlyprovidea
moreunifiedandstrategicapproachtosystemdesigninwearable singlespatialdimensionforeachtransducerelement.Therefore,
ultrasound. imagingsystemstypicallyemploy32ormorechannels.Inthe
Theconsiderationsbasedontheapplicationreviewmotivate commonline-by-line(sequential)scanningapproach,thetrans-
thestructureofthefollowingsections.InSectionIII,weexam- mitandreceiveaperturesaresteppedacrossthetransducerarray
inethefundamentalarchitecturalprinciplesandsystem-design toacquireechodatainboththeaxialandlateraldimensions[79].
requirements that underpin wearable ultrasound technologies, Thismethodofferscomputationalefficiencywhilemaintaining
emphasizing cross-domain commonalities that arise from the moderate resolution. However, its sequential nature limits the
challenges described above. Section IV then reviews current achievableframerate,anditsfieldofviewisrestrictedtoregions
system implementations, highlighting architectural strategies, neartheinsonationaxis,whichhasmotivatedthedevelopment
integrationconcepts,andemergingtrends.Together,theseanal- ofplane-waveanddiverging-wavescanningmethods[81],[82].
ysesidentifyopportunitiesformodularity,standardization,and Imaging systems are able to provide the same modalities as
platform-levelinnovationthatmayenablewearableultrasound non-imaging systems (A-Mode, M-Mode, Doppler) but can
toprogresstowardhigherTRLsandbroadersocietalimpact. alsoextendthemtoalateraldimensionwithB-Modesorcolor
Dopplerimages[79].Specificsystemdesignsalsoenableelas-
tographyimaging[58].
III. SYSTEMARCHITECTURE
Although both the non-imaging and imaging modalities de-
Duringultrasonicscans,anemittedacousticpressurewave- scribed above differ in terms of their transducer configuration
frontissentfromatransducerelementthatpropagatesthrough and achievable information content, they all rely on the same
the medium. Variations in material properties, such as tissue fundamental system architecture. Regardless of topology, the
boundaries or internal organ structures, cause partial reflec- hardware must generate ultrasonic waves, capture and digi-
tions or backscattering, which are individually captured by tize the returning echoes, and process them into meaningful
each receiving element, see Fig. 3. The purpose of ultrasonic outputs such as depth profiles, motion traces, Doppler-derived
systemsistodrivethetransducerstoperformthesescans,record flow velocities, frequency spectra, or images. This shared
theirsignalsandevaluateandtransmittherelevantinformation. generic architecture is illustrated in Fig. 4, outlining the main
Identifying key design specifications for wearable ultrasound functional blocks common to most ultrasound systems which
systems,requiresanunderstandingofcommonultrasoundmea- include:
(cid:2)
surementtechniquesandtheirtechnologicalimplications,which Atransmittingpaththatgeneratestheexcitationsignalto
areintroducedbelow.Buildingonthisfoundationweestablisha betransmittedbytheultrasonictransducer,
(cid:2)
genericsystemarchitecturewhosebuildingblocksaredescribed Areceivingpaththatconditionsanddigitizesthebackscat-
indetailinthefollowingsubsections. teredechos,
(cid:2)
Weproposeaclassificationschemeforwearableultrasound Acentralunitcontrollingtheseblockstoexecutespecific
applications, dividing them into two broad categories: non- sequencesandmaintaintimingconstraintsfortherespec-
imagingandimagingsystems.Non-imagingsystemscommonly tivemeasurementtask,and
(cid:2)
relyonpulse-echoscanningwithtypicallyuptoeightreceiving Anintegratedcomputingunitthateitherpre-processesthe
(RX)channels (seeFig.3(c)).Inmanydesigns,theconnected rawreceivedsignalsbeforetransmissiontoahostsystem
transducers are electronically multiplexed so that a single RX ordirectlycomputesanalyticalresults,e.g.flowvelocities.
channelcanscanallconnectedtransducerelementssequentially. Inthisregard,imagingsystemsaremerelyup-scaledversions
This approach minimizes power consumption and hardware of non-imaging systems to provide the increasing amount of

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
| 8   |     |     |     | IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026 |     |     |
| --- | --- | --- | --- | --------------------------------------------- | --- | --- |
Fig. 3. Overview of the functional and methodological variety of wearable ultrasound sensor systems. (a), application variety of sensors and
positions. (b), configuration transmitters (Tx), recievers (Rx) and signals of ultrasound sensor excitation. Functionality and specification of, (c),
non-imagingsystemsand,(d),imagingsystemsforscanningwithinthehumanbody.(e),typicalimagingmodalitieslike(AforAmplitude,Mfor
Motion or B for Brightness Mode) acquired on which, (f), information retrieval and processing form radiofrequency (rf-)signal to interpretation
is based upon. Information level in wearable systems range from raw data over acoustic signal properties and physiological data up to highly
processedsemanticinformation.
transmit (TX) and RX channels, processing capabilities, and specialized integrated circuits (ICs) [83] or a central measure-
databandwidth(seeFig.3(c)and(d)).Thefollowingsections ment control unit, which will be described in more detail in
| describeeachbuildingblockanditsspecificfunctionsinmore |     |     | SectionIII-D. |     |     |     |
| ------------------------------------------------------ | --- | --- | ------------- | --- | --- | --- |
detail. Driving ultrasound transducers also requires amplifying the
excitationsignaltothenecessaryACvoltagelevelsandadding,
|     |     |     | where applicable, | a DC bias. | In wearable | systems, gener- |
| --- | --- | --- | ----------------- | ---------- | ----------- | --------------- |
A. TX-Subsystem
|     |     |     | ating high | voltage amplitudes | poses significant | challenges |
| --- | --- | --- | ---------- | ------------------ | ----------------- | ---------- |
Ultrasonictransducersgenerateacousticpressurewaveswhen for size, power consumption, and crosstalk to the sensitive
electrically excited (Fig. 4, yellow blocks). Depending on the low-voltage RX circuitry. Moreover, multichannel operation
application,theexcitationsignalscanbepulsetrains,encoded can be achieved either through dedicated TX channels or
|                        |            |                         | by dynamically | routing a single | source to | multiple transduc- |
| ---------------------- | ---------- | ----------------------- | -------------- | ---------------- | --------- | ------------------ |
| signals, or continuous | waves (see | Fig. 3(b)). As depicted | in             |                  |           |                    |
Fig. 3(c) and (d), non-imaging systems can operate with just ers via high-voltage switches (e.g. high-voltage multiplexer
| asinglechannel,whereasimagingsystemsrequirethecoordi- |     |     | (MUX)). |     |     |     |
| ----------------------------------------------------- | --- | --- | ------- | --- | --- | --- |
natedexcitationofmultipletransducerchannels.Precisecontrol Beyond timing and driving electronics, the achievable per-
ofthedelaybetweenpulsesenablesthegenerationoffocused, formance also depends on the physical characteristics of the
diverging [82] or tilted plane waves beams [81], which form transducers themselves. The bandwidth, the radiation pattern
the basis for various beamforming and imaging schemes. The andamplituderesponseoftheexcitationsignalaredictatedboth
associated timing constraints can either be met by utilizing byapplicationneedsandbythesensoremployed.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 9
Fig. 4. Annotated block diagram illustrating the functional building blocks commonly found in ultrasound research platforms and commercial
devices.Thefunctionalgroupsarehighlightedasfollows:transmitpath(TX,yellow),receivepath(RX,aqua),centralcontrolunit(purple),and
computingunit(orange).ThegreyboxontherighthandsideillustratesperipheralsthatareincontactwiththewearablesystemsuchashostPCs,
mobilephones,tabletsorcloudservices.Abbreviations:ADC,analogtodigitalconverter;AWG,arbitrarywaveformgenerator;BLE,BluetoothLow
Energy;DSP,digitalsignalprocessor;FPGA,field-programmablegatearray;HV,highvoltage;MCU,microcontrollerunit;MUX,multiplexer;VGA,
variablegainamplifier.
In terms of operating principles, commonly used ultrasonic Direct sampling of RF data requires high-speed ADCs and
transducerscanbebroadlyclassifiedintotwomaincategories: acomputingsubsystemcapableofsustainingtheresultingdata
piezoelectricandcapacitive.Piezoelectrictransducers,typically rates.Incontrast,analogbandwidthreductiontechniques[87]or
fabricated from bulk ceramics such as lead zirconate titanate band-limitedexcitationwithdown-mixing[38]cansubstantially
(PZT), are widely used due to their strong electromechani- lowerprocessingrequirements,enablingsimplerandmoreeffi-
calcouplingandreliableexcitationperformance.Conventional cientsystemdesigns,particularlyforwearableapplications[88].
piezoelectricceramicsgenerallyachievefractionalbandwidths
| of up to | ≈ 60% | , while | single-crystal |     | piezoelectric | materials |     |     |     |     |     |     |
| -------- | ----- | ------- | -------------- | --- | ------------- | --------- | --- | --- | --- | --- | --- | --- |
C. Computing&CommunicationUnit
≈
| can extend | this | range | to 80% | [84]. | Capacitive | transducers |     |     |     |     |     |     |
| ---------- | ---- | ----- | ------ | ----- | ---------- | ----------- | --- | --- | --- | --- | --- | --- |
are typically realised as capacitive micro-machined ultrasonic Followingthedigitizationofthereceivedultrasoundsignals,
transducer (CMUT). CMUTs, in contrast, rely on electrostatic additional computation is required to extract relevant infor-
|           |                  |     |           |     |     |                   | mation with | following | communication |     | to  | the host interface |
| --------- | ---------------- | --- | --------- | --- | --- | ----------------- | ----------- | --------- | ------------- | --- | --- | ------------------ |
| actuation | of micromachined |     | membranes |     | and | are characterised |             |           |               |     |     |                    |
by inherently wide bandwidths, often exceeding 100% [84], (Fig.4,orangeblocks).Thecomputationprocesscanbedivided
intothreesubcategories:front-,mid-andback-endprocessing.
| [85]. Their | fabrication |     | with standard |     | semiconductor | processes |     |     |     |     |     |     |
| ----------- | ----------- | --- | ------------- | --- | ------------- | --------- | --- | --- | --- | --- | --- | --- |
allowsforcloseintegrationwithdigitalelectronics,whichmakes Front-end processing operates on the raw ultrasound data and
themattractiveforhighlyminiaturisedorarray-basedapplica- contains tasks like structuring multichannel data for further
|                 |     |       |           |         |     |                  | processing, | reducing | data-rate | by applying |     | IQ demodulation |
| --------------- | --- | ----- | --------- | ------- | --- | ---------------- | ----------- | -------- | --------- | ----------- | --- | --------------- |
| tions. However, |     | CMUTs | typically | require | a   | DC bias voltage, |             |          |           |             |     |                 |
sometimesgreaterthan100V,tooperateeffectively[85],[86], (if not already performed in the AFE) or applying beamform-
|     |     |     |     |     |     |     | ing algorithms. | Mid-end | processing |     | builds on | this by deriving |
| --- | --- | --- | --- | --- | --- | --- | --------------- | ------- | ---------- | --- | --------- | ---------------- |
whichcanposechallengesinbattery-poweredorfullyintegrated
systems. quantitative physiological data or structural parameters of the
specimen,suchasmotion,strain,ortissueproperties.Back-end
|     |     |     |     |     |     |     | processing | then interprets | these | parameters |     | within application |
| --- | --- | --- | --- | --- | --- | --- | ---------- | --------------- | ----- | ---------- | --- | ------------------ |
B. RX-Subsystem
|     |     |     |     |     |     |     | specific context, |     | generating | semantic | information, | integrating |
| --- | --- | --- | --- | --- | --- | --- | ----------------- | --- | ---------- | -------- | ------------ | ----------- |
withotherdatasourcesandpreparingresultsforvisualization,
| Upon | reception, | ultrasound |     | transducers | function | in reverse: |     |     |     |     |     |     |
| ---- | ---------- | ---------- | --- | ----------- | -------- | ----------- | --- | --- | --- | --- | --- | --- |
incoming echos mechanically excite the transducer elements, transfer or storage. The communication unit establishes and
which convert them into weak electrical signals in the mV- maintainsasecureconnectiontothehostinterfaceandtransmits
theprocesseddata,typicallyusingstandardizedprotocols.
| range. These | signals | are | routed | through | a MUX, | which maps |     |     |     |     |     |     |
| ------------ | ------- | --- | ------ | ------- | ------ | ---------- | --- | --- | --- | --- | --- | --- |
the individual transducer channels to the limited number of Theprimaryobjectiveofprocessingistoincreasetheinfor-
mationdepthbeforetransmittingthedatatothehost,asshownin
availableanalogfrontend(AFE)subsystemsandanalog-digital-
converter(ADC)channels(Fig.4,aquablocks).Ahigh-voltage Fig.3(f).StartingfromRFsignalswithhighsamplingratesand
protection stage, typically implemented as a TX/RX switch, correspondinglylargedatavolumes,computationaimstoextract
progressivelyricherinformationwhilereducingdata,ultimately
| enables | the same | transducer | to  | alternate | between | transmission |     |     |     |     |     |     |
| ------- | -------- | ---------- | --- | --------- | ------- | ------------ | --- | --- | --- | --- | --- | --- |
and reception without damaging the receive electronics. After reaching semantic representations. For example, while ADCs
channelmappingandisolation,thesignalsentertheAFE,where in the RX subsystem with sampling rates up to 10 times the
|               |     |           |     |         |          |                | emission | center frequency |     | [79] generate | output | data rates of |
| ------------- | --- | --------- | --- | ------- | -------- | -------------- | -------- | ---------------- | --- | ------------- | ------ | ------------- |
| amplification | and | filtering | are | applied | to match | the amplitude, |          |                  |     |               |        |               |
dynamicrangeandbandwidthoftheADC,therebymaximizing typically hundreds of Mbit/s, blood-flow velocity at a specific
arteriallocationcanbeexpressedwithonlyafewbytes,andits
sensitivity.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
| 10  |     |     |     |     |     |     |     |     | IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026 |     |     |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --------------------------------------------- | --- | --- | --- | --- | --- | --- |
semantic interpretation (i.e., healthy vs. pathological) may be and self-assessment of measurements. As devices should be
representedbyasinglebit. powered by small batteries while performing long-term mea-
This progressive reduction highlights the trade-off between surements,thepowerefficiencyofallelementsisakeydesign
localprocessingonthewearablesystemandtheamountofdata aspect. Including advanced processing algorithms directly on
thatmustbetransmittedwirelessly.Thebalanceishighlyappli- thewearabledevicecanimproveinformationthroughputwhile
cationspecificandsubjecttooptimization.Keyconsiderations reducinglatencyanddataraterequirementsforwirelesstrans-
forsystemdesigninclude: mission. To enhance integration and minimize size and power
(cid:2)
Latency due to a data link with limited bandwidth or consumption, the measurement control unit is often combined
processingwithrestrictedon-edgeresources, withthecomputingunitinasingleprogrammabledevice.Since
(cid:2)
Power consumption either by a wireless interface or a wearablesystemstypicallyrelyonwirelesslinks,reducingthe
processingunit,and required data rate can significantly lower power consumption
(cid:2)
Hardwarecostdrivenbyhighlyintegratedelectronics. andfacilitatesmallerformfactors.However,thiscomesatthe
|     |     |     |     |     |     |     |     | cost of  | more | complex    | processing | architectures |       | and             | memory, |
| --- | --- | --- | --- | --- | --- | --- | --- | -------- | ---- | ---------- | ---------- | ------------- | ----- | --------------- | ------- |
|     |     |     |     |     |     |     |     | which in | turn | introduces | additional |               | power | and integration | re-     |
D. MeasurementControlUnit
|     |     |     |     |     |     |     |     | quirements. | These | challenges |     | are compounded |     | by  | the need to |
| --- | --- | --- | --- | --- | --- | --- | --- | ----------- | ----- | ---------- | --- | -------------- | --- | --- | ----------- |
Thesequencerandmeasurementcontrolunit(Fig.4,purple
co-locatetheseresourcesalongsidesensitiveanalogelectronics
| block) combines |     | all components |     | that orchestrate |     | and | synchro- |            |     |               |     |        |     |         |             |
| --------------- | --- | -------------- | --- | ---------------- | --- | --- | -------- | ---------- | --- | ------------- | --- | ------ | --- | ------- | ----------- |
|                 |     |                |     |                  |     |     |          | of the RX- | and | TX-subsystems |     | within | a   | tightly | constrained |
nizeotherfunctionblocks.Theoperationofthisblockishighly
physicalenvironment.
relevanttothestabilityandqualityofthesystemasawhole:
(cid:2) Power efficiency is also imperative to reduce the device’s
| Multiple | elements |                       | of TX- | and RX-subsystems |         |            | have | to            |           |          |             |          |               |         |           |
| -------- | -------- | --------------------- | ------ | ----------------- | ------- | ---------- | ---- | ------------- | --------- | -------- | ----------- | -------- | ------------- | ------- | --------- |
|          |          |                       |        |                   |         |            |      | heat emission |           | in order | to minimize |          | skin heating, |         | which can |
| operate  | in       | tight synchronization |        | to                | produce | meaningful |      |               |           |          |             |          |               |         |           |
|          |          |                       |        |                   |         |            |      | limit the     | usability | in       | a wearable  | context. | Skin          | heating | is one    |
data,
(cid:2)
ofthesafetyconsiderationsthatpresentsuniquechallengesfor
Excitationhastobesynchronizedwiththesamplingpro-
|      |        |        |            |     |               |     |      | wearable   | ultrasound |       | systems.  | Unlike | conventional |           | diagnostic |
| ---- | ------ | ------ | ---------- | --- | ------------- | --- | ---- | ---------- | ---------- | ----- | --------- | ------ | ------------ | --------- | ---------- |
| cess | of the | ADC so | that echos | can | be associated |     | with | a          |            |       |           |        |              |           |            |
|      |        |        |            |     |               |     |      | ultrasound | systems,   | which | typically |        | operate      | for brief | clinical   |
(cid:2) depthinthespecimen,and
|            |               |             |       |       |         |       |          | examinations |            | (minutes), | wearable  | systems            |     | may be     | deployed    |
| ---------- | ------------- | ----------- | ----- | ----- | ------- | ----- | -------- | ------------ | ---------- | ---------- | --------- | ------------------ | --- | ---------- | ----------- |
| Subsequent |               | excitations | must  | occur | at a    | known | point    | in           |            |            |           |                    |     |            |             |
|            |               |             |       |       |         |       |          | continuously |            | for hours  | or days,  | significantly      |     | increasing | the         |
| time       | to facilitate | stable      | frame | rates | as well | as    | accurate |              |            |            |           |                    |     |            |             |
|            |               |             |       |       |         |       |          | likelihood   | of thermal |            | and other | ultrasound-induced |     |            | bioeffects. |
motionandflowvelocities.
Additionalsafetyconsiderationsincludeelectricalandmechan-
| The realization |     | of this | element | is very | application |     | specific |             |         |     |         |                      |     |     |              |
| --------------- | --- | ------- | ------- | ------- | ----------- | --- | -------- | ----------- | ------- | --- | ------- | -------------------- | --- | --- | ------------ |
|                 |     |         |         |         |             |     |          | ical device | safety, | as  | well as | the biocompatibility |     |     | of materials |
andcanbeachievedthroughtheutilizationofmicro-controller
|              |       |       |                    |     |     |             |      | in continuous |     | skin contact | in  | accordance |     | with ISO | 10993-1. |
| ------------ | ----- | ----- | ------------------ | --- | --- | ----------- | ---- | ------------- | --- | ------------ | --- | ---------- | --- | -------- | -------- |
| units (MCUs) | [15], | [89], | field programmable |     |     | gate arrays | (FP- |               |     |              |     |            |     |          |          |
Thebioeffectofultrasoundradiationontissueischaracterized
| GAs) [27] | or application-specific |     |     | integrated | circuits | (ASICs). |     |                 |     |                                     |     |     |     |     |     |
| --------- | ----------------------- | --- | --- | ---------- | -------- | -------- | --- | --------------- | --- | ----------------------------------- | --- | --- | --- | --- | --- |
|           |                         |     |     |            |          |          |     | bythemechanical |     | index(MI)andthethermalindex(TI).The |     |     |     |     |     |
Low-levelhardwarecontrolisrequiredinordertofulfillthestrict
|                     |     |              |     |                 |     |             |     | MI is related |           | to the | peak pressure |          | of the   | ultrasound    | wave, |
| ------------------- | --- | ------------ | --- | --------------- | --- | ----------- | --- | ------------- | --------- | ------ | ------------- | -------- | -------- | ------------- | ----- |
| timing constraints. |     | To configure |     | the measurement |     | parameters, |     |               |           |        |               |          |          |               |       |
|                     |     |              |     |                 |     |             |     | which is      | typically | not    | critical      | for most | wearable | applications. |       |
themeasurementcontrolunithastoexchangedatawiththehost
However,duetothelongexposuretimes,theTIistypicallymore
| system. In | addition, | a direct    | connection |                | to the | computing  | unit |              |     |     |       |          |          |            |     |
| ---------- | --------- | ----------- | ---------- | -------------- | ------ | ---------- | ---- | ------------ | --- | --- | ----- | -------- | -------- | ---------- | --- |
|            |           |             |            |                |        |            |      | significant. | The | IEC | 62359 | standard | provides | guidelines | for |
| allows for | automatic | adjustments |            | of measurement |        | parameters |      |              |     |     |       |          |          |            |     |
characterizingTIandMI.Inaddition,IEC60601-2-37defines
| based on | results | derived | from prior | measurements, |     | e.g. | selec- |     |     |     |     |     |     |     |     |
| -------- | ------- | ------- | ---------- | ------------- | --- | ---- | ------ | --- | --- | --- | --- | --- | --- | --- | --- |
thegeneralsafetyandacousticoutputrequirementsfordiagnos-
tionofspecifictransducerchannelsoradjustmentofrepetition
|     |     |     |     |     |     |     |     | tic ultrasound |     | systems, | which | also | apply to | wearable | devices |
| --- | --- | --- | --- | --- | --- | --- | --- | -------------- | --- | -------- | ----- | ---- | -------- | -------- | ------- |
intervals.
|     |     |     |     |     |     |     |     | insofar | as they | function | as  | continuous-operation |     |     | imaging or |
| --- | --- | --- | --- | --- | --- | --- | --- | ------- | ------- | -------- | --- | -------------------- | --- | --- | ---------- |
monitoringsystems.Theserequirementssetbaselinelimitson
E. ImplicationsandSafetyConsiderationsforWearable
|     |     |     |     |     |     |     |     | acoustic | exposure | and | system | performance. |     | Furthermore, | the |
| --- | --- | --- | --- | --- | --- | --- | --- | -------- | -------- | --- | ------ | ------------ | --- | ------------ | --- |
Systems
AmericanInstituteofUltrasoundinMedicine(AIUM)provides
Fromasystemicpointofview,thefunctionalelementsofa aguidelineformaximumscanningtimesinrelationtoTIin[90].
wearableultrasoundsystemdescribedabovedonotdifferfrom Ref.[29]providesacomprehensiveoverviewofexistingnorms
aclinicalorlargeresearchsystem.Themaindifferenceliesin andregulations,aswellastheirapplicabilitytonovelwearable
the requirements that a wearable system must meet. Wearable ultrasoundapplications.
devicesaremostlytobeusedwithoutthefrequentintervention
| of trained | personnel | to allow | long-term |     | measurements |     | in non- |     |                                 |     |     |     |     |     |     |
| ---------- | --------- | -------- | --------- | --- | ------------ | --- | ------- | --- | ------------------------------- | --- | --- | --- | --- | --- | --- |
|            |           |          |           |     |              |     |         | IV. | STATEOFTHEART:WEARABLEDESIGNAND |     |     |     |     |     |     |
clinicalenvironments.Thisscenarioposesadditionalconstraints
INTEGRATION
ontheimplementationofthedescribedfunctions.Allbuilding
blocks must be highly integrated to realize a wearable system Buildingon thegeneric overview, thissectiontargets anin-
thatdoesnotrestrictmovementormobility. depthreviewofthecurrentstateofwearableultrasoundsystem
Theamountofprocessingintegratedintothedevicedepends design,exploringanswerstothefollowingkeyquestions:
(cid:2)
on the application, as the complexity can range for imaging Whatdesignstrategieshavebeenemployedtoovercome
andnon-imagingmodalityfromsimplespectralprocessinglike thechallengesinwearableultrasoundsystems?
(cid:2)
filteringuptoneuralnetworkprocessingforimageclassification Whattrade-offsareinvolved?

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 11
(cid:2)
Whattrendsandopportunitiesareemerging? as sequencer, measurement controller and computing unit. It
Followingthetaxonomyestablishedintheprevioussection, generates control signals for the TX and RX subsystems and
wedistinguishnon-imagingsystems(SectionIV-A)andimag- performs data management and processing. The DSP collects
ingsystemsbothbasedonthepulse-echomethod(SectionIV-B). data from a buffer and transmits it to the communication IC
Inaddition,thereisagrowingfractionofwearablesystemsthat (Ethernet or Wi-Fi). Although the Ethernet IC supports data
arenotbasedontraditionalpulse-echo,topotentiallysimplify rates of up to 30 Mbit/s, only 0.1 Mbit/s were demonstrated,
theirsystemdesignandreducepowerconsumption,whichare which corresponds to a frame rate of 10Hz; likely being lim-
discussedinSectionIV-C. ited by other system factors. From there, A-mode scans were
An overview of the systems, along with their design and transmitted to a host PC for further processing. The hardware
specifications,isprovidedinTableI.WithinTableI,anenergy weighs190gandconsumes3.5W,whichgivesanenergyper-
performance ratio is provided for a generic comparison of the formanceratioof0.03Mbit/J.Poweredbya3000mAhbattery,
differentapproaches.Itisdefinedasthedataratedividedbythe the system can operate continuously for 10h. The platform
powerconsumption,expressedinMbit/J.Thisratioiscommonly was later commercialized by [101], which paved the way for
usedinwirelesscommunicationandsustainablecomputing[91] furtherstudiesinthisfield[71],[96],[97],[98].Furthermore,a
and is here adopted for wearable ultrasound systems. Since multimodalversionthatincorporatesfoursEMGsensorsalong-
channelcount,framerate,pulserepetitionfrequency,andpro- side four ultrasound probes in a wristband was also reported
cessingcomplexitydirectlyaffecttheresultingdatarate,theratio [99],[100].
providesanintegrativemeasureofdeliveredsystemthroughput Ref.[89]presentedare-designofWMAUScloselyintegrated
per energetic cost. Additional information on the performance into a prosthesis. It is centered around the STM32F7 micro-
metricsandthecalculationisprovidedintheSupplementSec- controller instead of the previously used DSP. In contrast, this
tion2. system uses a much lower ultrasound frequency (1MHz) and
sample rate (2.4 MS/s). It weighs only 85g and achieves an
increased data rate of 1 Mbit/s. Despite the increased power
A. Pulse-EchoNon-ImagingSystems
consumption, the energy performance increased to 0.2 Mbit/J.
1) Closed Systems: Various non-imaging systems based With a 1500 mAh battery, continuous operation for 3.5h is
onpulse-echoultrasoundalreadyreachedcommercialavailabil- possible.Todate,nostatementshavebeenmaderegardingthe
ity (CA), helped by their lower architectural complexity com- availabilityofWMAUSanditsre-design.
paredwithimagingsystems(cf.SectionII).Aprominentexam- In [103] introduced WULPUS, a wearable ultrasound plat-
pleisportablefetal–maternalmonitoring,wherecompactform form for carotid artery and muscle activity monitoring. It was
factors have measurably improved wearing comfort [52]. For specifically developed to enable multi-channel A-mode scan-
bladdermonitoringinpersonswithincontinence,fullywearable ningwithlowpowerconsumption.Thedeviceweighsonly9g
A-mode solutions from [36] and [62] exemplify the category. andmeasures46×25×13mm3.WULPUSiscenteredaround
SENS-U adheres to the lower abdomen using an adhesive and the MSP430FR5043 (Texas Instruments), an ultra-low-power
couplinggel[92],employsfourA-modetransducerstorealizean system-on-chip (SoC). This SoC integrates a programmable
effectivefieldofviewof30◦,andestimatesfillinglevelbytrack- ultrasound pulse generator, an analog front-end (AFE) with
ingbladderwallpositionsovertime.Measurementsaresentvia amplifier and ADC, and a 16MHz RISC CPU. The ADC
Bluetoothtoasmartphoneapplicationthatissueshigh-fillalerts. samples data with 12 bit at 8MHz. Single, trill, and multi-
Thedeviceweighs55g includingthebattery,supportsatleast tone pulses can be generated with a mid-frequency of up to
36hofcontinuousoperation,andusesitsfour-elementlayoutto 4MHz.Regardingpowerconsumption,theSoCprovidesthree
self-assessplacementandprovideintuitiverepositioningcues; modes:active(0.12mA/MHz),standby(450nA),andshutdown
specificationsaresummarizedinTableI.Unfortunately,dueto (30nA).Thehighlevelofintegrationandlow-poweroperation
their closed system design, despite their maturity and market maketheSoChighlyattractiveforwearableA-modeultrasound
availability,thesedevicescannotserveasgenericplatformsfor applications. For this purpose, [103] complemented the SoC
relatedapplications. withahigh-voltagePCBforpulseamplification,HVprotection,
2) Open Research Systems: Towards generic platforms, andmultiplexingtoeightindividualtransducers.Anadditional
thissectionfocusesonopenresearchsystemsthatprovideaccess SoC(nRF52832,NordicSemiconductors)transmitsthedatavia
to raw data, offer programming interfaces, and enable modu- BluetoothtoahostPCwithadatarateof300kbit/s.WULPUS
larity. In [80] introduced the wearable multichannel A-mode isfullydocumentedandavailableopensource[106],including
ultrasound system (WMAUS). This system was subsequently hardware schematics, PCB layouts, firmware, front-end and
employed in several works of the same group targeting hand back-endsoftware,andadetailedmanual.
gesturetrackingforhuman-machineinterfaces[64],[93],[94], Refs.[69],[70]integratedWULPUSintoawearablearmband
[95]. WMAUS consist of a customized wristband with eight withthreeultrasoundprobes,eachcontaininga32-elementarray
individualultrasoundtransducers,featuringacenterfrequency at 2.25MHz. The four left- and rightmost elements of each
of5MHzandabandwidthof77%.Thechannelsaredrivenin probe were connected in parallel, resulting in six individual
timedivisionmultiplexing(TDM)andsampledaftertheanalog A-mode transducers that acquired signals at a pulse repetition
front-end at 20 MS/s. The core of the WMAUS hardware is rate of 25Hz. WULPUS also demonstrates a high degree of
the digital signal processor (DSP) dsPIC33, which is active edgeprocessing:usingembeddedAIforfeatureextractionand

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
12 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
TABLEI
OVERVIEWOFSTATE-OF-THE-ARTSYSTEMS.ASWITHTHEMAINTEXT,THETABLEISDIVIDEDINTHETHREEPARTSOFNON-IMAGING,IMAGINGAND
NON-PULSE-ECHOSYSTEMS,WHEREASFOREACHCONTRIBUTIONTHETRANSDUCERINTERFACE,TX-ANDRX-PATH,COREHARDWAREDESIGN,THE
DATALINKANDBASICPROPERTIESARESPECIFIED.ANEFFICIENCYMETRICISCALCULATEDBASEDONTHEACTUALDATALINKBANDWIDTHNORMALIZED
TOTHEPOWERCONSUMPTION.FURTHERMORE,INFORMATIONISGIVENUPONITSDEMONSTRATEDAPPLICATIONANDACCESSTOTHEHARDWARE.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 13
classification on a separate microcontroller, the system recog- MoUsE has been employed by [66] as a human–machine in-
nizesgesturesfromrawultrasounddatainrealtime.Ref.[70] terface for wrist and hand tracking [66] and for prosthetic
reportatotalpowerconsumptionof28mWforfromultrasound control[108].
scanning to feature detection and transmission. This enables An open programmable POCUS platform, the OEM USB
morethanthreedaysofcontinuousoperationwitha320mAh Probe, is provided by [27] for research and development of
battery. With its lightweight design and strong energy perfor- new applications, see Table I. It supports 128-channel probes
manceof11Mbit/J,thesystemachievesgesturerecognitionac- withmid-frequenciesupto8.5MHzandisfullyprogrammable.
curacycomparabletootherworksthatrelyonlargerdevicescon- Several probe types are available targeting medical imaging
suming ≈ 70 times more power [99]. Furthermore, WULPUS applications such as liver, brain, heart, vascular system, or
has been used for heart rate and respiration monitoring [104], muscles. In addition, it can operate 32-channel probes with
wherethesameultrasoundarraywasconfiguredtocombinethe mid-frequenciesupto3MHz.
innereightelementsforA-modeandM-modeacquisitions. WhilePOCUSdevicesarevaluableforproof-of-conceptstud-
Very recently, [88] proposed PuLsE, a compact wrist-worn ies,theyareusuallynotsuitableforwearableapplicationsdueto
ultrasound heart rate monitor. It features a single transducer theirsizeandweight.Additionally,theirpowerconsumptionof
channelthatcanbeexcitedupto10MHzwithapulserepetition typicallymorethan1Wrequireslargebatteriesformulti-hour
rate of 25Hz. The design is straightforward: it integrates an useandleadstoheatemissionreducingwearingcomfort.
STM32L496 MCU for digitization, sequencing, and compu- 2) Wearable Systems: From the pioneering POCUS de-
tation, a Bluetooth module (nRF52832), an ultrasound pulser vices, platforms emerged in recent years to fully target wear-
(STHVUP32), and a custom AFE [87]. With a cascade of able ultrasound. Ref. [15] proposed USoP in [15] as one of
amplifiers, diode rectifiers, and a low-pass filter, an envelope the first wearable imaging platforms. The hardware was built
compressionisperformed.Thislowersthenecessarysampling around a PIC32 microcontroller (Microchip Technology Inc.),
rate to 5 MS/s, which is substantially less than what would that served as a data acquisition module. It samples the data
be required for directly sampling, as the transmitted pulses of one channel at once with 12 bit at 12MHz and transmits
haveacenterfrequencyupto10MHz.TheMCUthendirectly it via a Wi-Fi IC with 3.4 Mbit/s to a host device for further
processes the heart rate from the M-mode. This minimalistic processing.Asecondmicrocontrollerperformsthesequencing
designachievesthelowestreportedpowerconsumptioninthis andmeasurementcontrol.OnlyoneRXchannelcanberecorded
fieldwithonly5.8mW,likewiseachievingthehighestenergy atonce,butfastmultiplexingover32channelsallowsaB-mode
performanceratioof52Mbit/J.Thesystemiscurrentlyrealized reconstructiononthehostdevice.Thepulserepetitionfrequency
using the modular ultrasound development platform, Modu- of USoP is 1kHz, resulting in an overall frame rate of 31Hz.
lUS[113].Thisplatform-basedimplementationenablesflexible A unique feature of USoP lies in its level of integration as a
experimentationandreproduciblevalidationofsensingandpro- wearabledevice.WithitsflexiblePCBandboardconnectors,it
cessingpipelines,whiledeliberatelydeferringformfactorand wasespeciallydevelopedtobewornonskin.Largerintegrated
weightoptimizationtolaterintegrationstages.Infutureworks, componentsareplacedonopposingsidesofthePCBtoincrease
integration into a watch-like device (40 mm diameter, 10 mm flexibility,allowingforamaximalbendingangleof24.1◦.The
height, 15g weight) is planned. Ref. [88] also announced an authors measured a power consumption of 614mW, lasting
open-sourcerelease,whichwasnotyetavailableatthetimeof forupto12hoperationwhenpoweredwitha“standard3.7V
writingthisreview. commerciallithium-polymerbattery”.Theenergyperformance
of USoP accounts to 5.5 Mbit/J. A rough overview of the
schematicsandthePCBlayoutisprovidedinthesupplementsof
B. Pulse-EchoImagingSystems
thearticle[15],however,replicatingorbuildingupontheUSoP
1) Non-Wearable Origins: Research and development of design is hindered by the lack of publicly available hard- and
wearable ultrasound imaging systems are strongly linked to softwaresources.
the introduction of point-of-care ultrasound imaging systems Recentlyin[83]proposedTinyProbe.Itisahighlycompact
(POCUS).InaPOCUSdevice,thetransducerarrayisintegrated imaging platform with dimensions of 57 × 35 × 20 mm3 and
withallsystemcomponentsmentionedinFig.4andconnected apowerconsumptionrangeof0.4to1.2W.Theactualpower
via USB or Wi-Fi to a host device such as a smartphone or consumption depends on the mode of operation and the used
tablet[25],[26],[27]. pulse repetition frequency. For a typical imaging sequence,
TheincreasingavailabilityofPOCUSdevicesinrecentyears TinyProbeconsumes0.97Wwithanenergyperformanceratio
has accelerated the development of wearable applications and of 22 Mbit/J, for which [83] ensure a 2h battery lifetime. At
systems: [114] used a portable ultrasound device to measure itscore,amicrocontrolleroftheSTM32F4familycontrolsthe
muscle thickness during a treatment exercise. Ref. [115] used Igloo2FPGAsequencerandbuffersthedatafortheWi-FiICto
a POCUS device to generate biofeedback of muscle motion betransmittedtoahost.Sofar,theauthorsonlyusedTinyProbe
to improve rehabilitation outcomes. Furthermore, a POCUS for raw data acquisition with offline post processing on a host
devicewasusedby[116]toprovideuser-specificassistancefor PC.Nevertheless,anSoCforedge-computingapplications[117]
exosuits,resultinginmeasurablemetabolicbenefits.Ref.[107] is already integrated, which the authors will evaluate in future
proposed MoUsE, an open platform for POCUS applications. works. It is also worth mentioning that TinyProbe is the first

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
14 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
platformofthatsize,weightandpowerconsumptiontoincorpo- is demodulated into a 100kHz baseband signal by a custom
rate32channelTXbeamformingandRXrecording.Firmware, analog circuit. For digitization, a 40 kS/s ADC is sufficient,
schematics and design files of TinyProbe are available open resultinginathreeordersofmagnitudelowerdataratecompared
source[109]. totypicalpulse-echosystems.Asaresult,theMCU-integrated
ADC could be used, reducing the overall system’s complexity
(cf.TableI).Ref.[38]demonstratedthepracticalfeasibilityby
C. NonPulse-EchoSystems
achieving simultaneous four-channel ultrasound imaging at a
Medical ultrasound systems typically use high-frequency, framerateof50Hzwithapowerconsumptionof0.82W,corre-
short-duration pulses on combined TX/RX transducers to spondingwithanenergyperformanceratioof1.1Mbit/J.Asthe
achieve spatially resolved measurements. Due to the strong results were obtained with development boards, a much lower
attenuationofultrasoundwavesinthehumanbody,high-voltage power consumption and smaller form factor can be expected
pulsesintransmitandlow-noiseamplifiersinthereceivingpath through further integration and optimization. No information
arerequiredtoachieveasufficientsignal-to-noiseratio(SNR). ontheavailabilityofcodeandhardwaredesignsisgiveninthe
Furthermore, the analog to digital conversion typically must paper.
occuratleastatfourtimesthecenterfrequencyofthetransmitted Ref.[123]introducedasteppedchirpforultrasoundsensing.
signal to capture the full bandwidth of the echo signal [118]. Targeting early implant-failure detection, their in silico study
The power consumption of high-voltage pulse generators and usesseparatetransmitandreceiveunitsforsimultaneousTXand
thedigitizationandtransferoflargeamountsofdataposemajor RX.Eightsmallpiezo-transducerswereembeddedinaflexible
challenges.Thissectionfocusesonsystemsandapproachesthat cuffthatistightenedaroundthejointofinterest.Anultrasound
employothersignaltypestoaddresssomeoftheshortcomings lowfrequencychirpfrom1to300kHzin1kHzstepswasused
ofpulse-echoultrasound. toscanthecorticalboneandtheimplantinterface.Amachine
1) Continuous Wave Approaches: Refs. [47], [111], learningalgorithmdetectedandclassifiedpossiblehipimplant
[119],[120]and[121]introducedanadhesivecontinuouswave failure and its severity. With this study, [123] demonstrated
Doppler patch for real-time monitoring of blood flow velocity the potential of power efficient low-frequency ultrasound and
inthecommoncarotidartery.Thedeviceusestwo4MHztrans- data-drivenprocessingforinexpensivepoint-of-carescreening
ducersforcontinuoustransmissionandreception.Ahomodyne ofimplantintegrity.However,lackingacapablehardwareplat-
demodulator extracts the Doppler signal from the received RF form,thestudywasonlyconductedinsilico.
data into an audio-band signal. Every 12.8 ms a new Doppler 3) Coded Excitation Approaches: Coded excitation
signal is extracted, providing near-real-time data essential for schemestypicallyincorporatepulsecompression[124],[125],
capturingdynamicbloodflowchangesinclinicalsettings.This a technique originating in radar systems, to spread the same
approach is beneficial for the integration in a wearable, as the transmit energy over a longer, lower-amplitude waveform and
data processing and communication for audio-band signals in subsequently recover axial resolution during post-processing.
the kHz-range operates with much lower sampling rates than This makes them particularly attractive for wearable systems,
ultrasound signals in the MHz-range. Therefore, small-sized where the stringent requirements for power efficiency, form
andefficientcustomASICsorFPGAscouldbeemployedasthe factor,andcostnecessitatedrasticcompromises,especiallywith
computation unit [122]. The system is commercially available respecttoacousticalperformance[126]andsystemdesign.The
through[35]. resulting SNR loss can be compensated through coding gain;
IncontextofDopplerbloodflowmeasurement,theestimated however, it strongly depends on the type of signal employed
velocitydependsontheinclinationanglebetweentheultrasound andfurtherinfluencesthecomplexityoftheanalogelectronics
beam and the vessel direction, which is typically only known aswellasthespatiotemporalresolution.
approximately.Toreducetheerrorsofamispredictedangle,[48] In[112]proposedanultrasoundsystemasapre-voidingalarm
proposed a 3 × 3 angled transducer patch that allows for esti- system for children with nocturnal enuresis based on Barker
matingtheinclinationangle.However,nofullywearabledevice codedpulseexcitation.Barkercodesaretwo-level(±1)pulse-
wasdemonstrated,asitreliesonexternalequipmenttooperate. compression sequences that allow for low-voltage excitation
2) Chirp Approaches: In [38] proposed time-delay spec- amplitudes [125]. The authors used a 5 bit Barker code that
trometryforlow-voltagedynamictissueimaging.Acontinuous isphase-modulatedonaseven-cycle1.95MHzcontinuoussine
linear chirp is used as excitation signal, where the excitation waveandamplifiedto±10Vfortransmission.Alineararray
frequency increases over time, see Fig. 3(b). The chirp prop- consistingofelevensquareultrasoundtransducerelementswas
agates into the tissue, where each scatterer returns a time- employed, where sequential pairwise transmit–receive opera-
delayed, attenuated echo of the signal. The time delay, which tions were performed and processed through a matched filter.
is proportional to depth, correlates to a frequency difference. By means of pulse compression, an SNR gain of 12.6 dB was
An increasing depth results in a longer delay and a higher achieved. The prototype was implemented using development
frequency shift between the transmitted and received signals. boards,alargedigitizationdevice,andcomputationonaPCvia
Using demodulation and Fast Fourier Transform, an A-mode USB,buttheapproachshowspotentialforfurtherintegrationto-
is reconstructed from the received signal. In their design, [38] wardsreducedpowerconsumptionandsmallerformfactors.No
employed chirps from 3MHz to 5MHz in 10 ms that are statementsweremaderegardingtheavailabilityoftheproposed
amplifiedtoapeak-to-peakvoltageof5V.Thereceivedsignal system.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 15
Another Barker-code-based pulse compression method was reducewirelesstransmissionloadtooptimizeenergyefficiency
proposed by [127]. In their in silico study, a transducer with a andlatency.Together,thesestrategiesenableincreasinglycom-
centerfrequencyof10MHzwasusedtotransmita13-bitBarker pact,efficient,andversatilewearableultrasounddevices.
code modulated with a bipolar pulse. In contrast to previous 2) Trade-Offs: Balancing functionality within ultra-low
works,[127]employedmismatchedfilteringcombinedwithin- power demands and size constraints represents the key design
phase quadrature compression. The authors demonstrated that trade-off for the ultrasound wearables investigated, which is
this approach enables efficient data compression with reduced characteristicofwearablesystemsingeneral.Whatisuniqueare
computationalcomplexitywhilemaintainingimagequality. thechosendesignroutes.DecreasingthenumberofRXchannels
Ref.[128]demonstratedGolay-codedexcitationforrotational and relying on multiplexing is an effective compromise [36],
intravascular ultrasound to cancel range sidelobes while pre- [80],[103],[112].However,thisdrasticallylimitstheachievable
servingaxialresolutionusingweightedaveragingcompression. framerate of imaging systems [15]. Ref. [83] showed that the
Based on this, [129] implemented realtime ultrasound biomi- numberofRXchannelscanbeincreasedusingdedicatedlow-
croscopyat30MHzusing4-,8-,and16-bitGolaypairs,increas- power integrated circuits. Large data volumes necessitate fast
ingdetectiondepthandSNRwithoutdegradingaxialresolution. wireless links [15], [83], [89] or on-device compression [38],
However,atranslationofGolay-orBarker-codedexcitationto [70], [88], shifting power consumption to communication or
wearableultrasounddevicesremainstobedemonstrated. computation circuitry. Flexible and thin mechanical designs
Although not in a medical context, [130] presented a novel improvecomfortbutrestrictcomponentplacement,cooling,and
low-powerhardwarearchitecturebasedonlongpseudo-periodic high-voltageisolation[15].Fullyintegratedclosedsystemsare
coded excitation. The approach drastically reduces electronic efficientbutlackconfigurability[35],[36],whereasopenplat-
complexity by directly coupling transmission and receiving formsareadaptablebutoftenbulkierandlessoptimized[106],
circuitry, operating them simultaneously within the same low- [109].Overall,thesecompetingconstraintsshapethearchitec-
voltagerange(±2V).Thiseliminatestheneedforhigh-voltage tureschosenforwearableimplementations.
generation,transmit–receiveswitching,andlow-noiseamplifi- 3) Trends & Opportunities: The field is trending toward
cation,albeitatthecostofaseverelyreducedSNRintheraw edge-intelligentwearablesthatperformreal-timeinferenceon-
signals. The recorded waveforms are dominated by the trans- device, reducing data transmission requirements and enabling
mit signal with weak superimposed echoes; however, through autonomousoperation[70],[88].Publicationsareemergingwith
matchedfilteringtheimpulseresponseofthespecimencanbe low-voltage and low-data-rate ultrasound approaches, such as
reconstructedandcodinggainrealized.Intheirproof-of-concept continuous wave [119], [121], chirp scanning [38], [123], and
demonstrationsfornon-destructivetesting,theauthorsachieved codedexcitation[112],[127],[130],whichpotentiallysimplify
comparable SNR to state-of-the-art high-voltage ultrasound hardware and lower power consumption. Miniaturized multi-
equipment(200Vexcitation)whileoperatingatlowvoltage,and channel systems now incorporate low-power FPGAs and/or
furthershowedthefeasibilityofmulti-channeloperationusing MCUs[15],[83],pushingimagingsystemsclosertopracticality
quasi-orthogonal TOP-CS codes. So far, the system has only whilst maintaining a high degree of flexibility. Open-source
beenrealizedwithlaboratory-gradeequipment,andnotransla- hardwareplatformsareexpandingaccesstohigh-qualityimag-
tiontomedicalorwearableapplicationshasbeendemonstrated. ing and sensing tools for research and innovation [88], [106],
Nevertheless, the combination of ultra-low excitation voltage [109]. Flexible, skin-conformal electronics are enabling long-
and simplified hardware requirements makes a translation to termphysiologicalmonitoringineverydaysettings[15].
wearableultrasoundsystemsdesirable.
V. DISCUSSION
D. Summary A. CurrentLimitations
Thissectionconcludeswithaconciseoverviewaddressingthe One of the central limitations comes with the capabilities
initial questions on design strategies, trade-offs, and emerging wearablesystemscanachievegiventhestrictdemandsinform
trends. factor and power efficiency. Due to its simplicity and data ef-
1) Design Strategies: Wearable ultrasound systems in- ficiency,non-imagingultrasoundmodalitiesarehighlyrelevant
creasinglyrelyonhighintegration,usingMCUs,DSPs,andlow- for wearable applications [46], [80], [92], [103]. Information
powerSoCstocombinepulsegeneration,reception,digitization, aboutmovements,pulsationsandphysiologicalchangescanbe
and processing into compact electronics. Flexible PCBs and acquiredfromdeepinsidethebody.Non-imagingsystemswere
distributed component placement help achieve skin-conformal shown to provide accurate results for HMI applications [80],
formfactorswithoutsacrificingessentialfunctionality[15].To [99],[108]andphysiologicalmonitoring[15],[88],[104],[131].
reducedataratesandcomplexity,manysystemsadoptstrategies They can be highly integrated to a lightweight system with
such as envelope detection [88], analog demodulation [38], or low-power consumption, enabling a multi-day use of a fully
pulsecompression[112].Modularopensourceplatforms[106], wearable device with only a single charge [70], [104]. As a
[109]enablerawdataaccess,userprogrammability,andrecon- consequence, up to now available and fully wearable devices
figurablesensingsetupsforresearchapplications.Edgeprocess- arebasedonnon-imagingscans[36],[52],[62].Themajordis-
ing[38],[88]andembeddedAI[69],[70]arebecomingcentral advantageofnon-imagingmodalitiesistheuncertaintyofspa-
designelements,allowingdevicestointerpretsignalslocallyand tiallocalization,requiringwell-trainedpersonnelorautomated

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
16 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
evaluationandfeedbackforsensorplacement[36].Thisisman- This critical trade-off for wearable system design needs a
ageable for larger objects like bladders, but is problematic for complex balance of energy consumption, heat emission, data
theplacementonfinerstructuressuchastheheart,musclesand rate,computationalworkloadandformfactor[16].Ononehand,
arteries. computationalworkloadon-edgetowardssemanticinformation
Imaging systems on the other hand allow for a tracing and isbeneficialforalowerdatathroughput,allowingforlow-power
compensation of motion facilitating an observation and evalu- communication standards as for instance Bluetooth [69]. But
ation of complex physiological changes and patterns. From a on the other hand, large computation workloads may increase
transducer perspective, wearable imaging has seen significant energy consumption and heat emission above a level that is
advancementstowardsconformablesensors.Examplesinclude feasible for a wearable system. For imaging systems, this is
the flat-panel PMUT array developed by [51], the BAUS-E even more critical because of the increased number of chan-
systemby[58]forwearableelastography,andtransducerarrays nels to be excited, recorded and processed. Hence, the chal-
based on liquid metal electrodes [49], advanced piezoelectric lenges to the integration of a fully wearable imaging device
ceramics [132], lead-free piezoelectric polymers [133], or sil- are much more severe compared to non-imaging devices [83].
icon CMUT arrays [134]. However, to drive these transducers Two potentially wearable imaging platforms were introduced
a platform capable to excite, record and process these multi- sofar,namely USoP[15]and TinyProbe [83].They can serve
ple channel transducer arrays is required. Wearable elastogra- as open research platforms given their availability. Yet, their
phy [58] furthermore requires push-beam excitations as well data acquisition, computation and link-to-host capabilities are
asthecapturingandprocessingofmorethan1000imagesper not sufficient to exploit the potential given by recently pub-
second, which is far beyond the capabilities of state of the art lished conformable transducer arrays. For instance, to correct
wearablesystems[15],[83].Furtherlimitationsaregiveninthe alldegreesoffreedomoftheconformablearrayof[49],aplat-
data bandwidth and real-time processing capability required, formto drive all348 elements individually including TX- and
whichisyethardlypossibletobeachievedwithinformfactors, RX-beamforming is necessary. This equals eleven TinyProbe
power consumption and heat emission that wearable applica- platforms,addinguptoapowerconsumptionof≈11W.Sus-
tionsdemand.Asaresult,alltheseadvancedtransducershave tainedoperationabove1Wisgenerallyimpracticalforcompact,
sofarbeenoperatedusinglargeresearchplatforms.Therefore, skin-worndeviceswithmulti-hourbatterylifetargets,because
itisreasonabletoassumethatthefirstapplicationsofwearable it implies large batteries and increased heat dissipation. One
imagingtransducerswillemergeinclinicalsettingsonimmobile key bottleneck is technological: no integrated circuit currently
patients,wheretheuseofalargerplatformisnotalimitingfactor. combinesanultrasound-gradeanalogfront-end,thelow-power
Fornon-imagingtransducers,clinicalstudiesalreadyexist[46], control and tightly coupled memory architecture typical for
andforimagingapplications,itislikelyonlyamatterofafew microcontrollers, and the high-speed, sequencing and parallel
yearsbeforesimilarstudiesarepublished. processingcapabilitiesofFPGAsintoasingleICoptimizedfor
The introduction of wearable imaging transducers for mon- low-powerwearable-ultrasound.InthecaseofTinyProbe[83],
itoring purposes in hospitals within the next five years there- thisfunctionalityisdistributedacrossthreeseparateICs,namely
fore appears realistic, especially since, for example, Pulsify ananalogfront-end,amicrocontroller,andanFPGA.Integrating
Medical’s wired transducers are already approved as medical thesefunctionsintoadedicatedwearable-ultrasoundsystem-in-
devices[50].However,fullywearablesystemsintendedforuse package (SIP) or ASIC would reduce inter-chip communica-
outsideofclinicalenvironmentsonmobilepatientsstillrequire tionoverhead andboard-level complexity, and isthereforeex-
considerableresearchanddevelopmenteffortsinsystemdesign. pectedtosignificantlyreduceenergyconsumptionandphysical
This is in contrast to the non-imaging systems, where already dimensions.
severalproductsemployingsingletransducersareavailableand Considering parameters such as the achievable compute-
completelywearable[36],[52],[62]. per-milliwatt of existing microcontroller units, the bandwidth
and energy cost of commercial wireless links, and the PCB
footprintofprogrammablefront-endcomponentsindicatesthat
B. System-LevelConsiderations
modular, scalable platforms are technically attainable for low-
Ouranalysisrevealsthatthemajorityoflimitations,especially to mid-complexity sensing tasks. For full imaging pipelines,
formoreadvancedapplicationsandtransducers,arelimitations especiallyconformablearrays,theyareonlymarginallyfeasible
of the system design. Therefore in this section we further with current technology. Bridging this gap will require both
analyze recurring architectural considerations across wearable architectural innovation and advances in device technology,
ultrasoundsystems. potentially complemented by alternative operating paradigms
1) Design Trade-Offs: Wearable devices necessitate a suchasnon–pulse-echoimagingschemesorenergy-harvesting-
trade-offbetweentwoconflictingobjectives: assisteddesigns[135].
(cid:2)
Thenecessitytointegratecomplexprocessingunits[20], 2) Unsupervised Reliability: Long-term unsupervised
whichposechallengesinintegration,powersupplycom- measurements require a stable measurement setup and,
plexityandmemoryrequirements. potentially,theself-assessmentofrecordeddata[29].Thiscan
(cid:2)
Theconcernofreducingdata-linkbandwidth[103],par- berealizedbyeithertransferringultrasounddatatoahostsystem
ticularly in wireless implementations where power con- for further evaluation or by integrating advanced processing
sumptionisacrucialfactor. capabilities into the wearable device [20], [69]. Specifically

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 17
for imaging systems, conformable transducer patches enabled data rate than WiFi, but the ICs consume much less power.
worn, unsupervised operation in the first place, but for If the system is able to scale down to the lower Bluetooth
reliable image reconstruction accurate self-calibration of the data rate, low power systems that work for several hours are
deformabletransducerelementsisrequired[31].Sofar,several achievable [69], [88]. Here, ultrasound wearables can benefit
self-calibration approaches were reported, such as software from the developments in communication standards and ICs
basedshapeestimation[136],opticalshapesensingfibers[137] drawn from other wearables and IoT devices. This approach
or electrical sensing of element-intercapacity-changes [134]. enablesfastprototyping,butencounterslimitationsforclinical
Eachofthemmoreorlessincreasessystemcomplexityandadds environmentsthatoperateonDICOMandPACSstandards.
to the computational workload [31], increasing the dilemma 5) Non Pulse-Echo Systems: Most works on ultrasound
concerningdata-rateandon-edgeprocessingcapabilitieswithin wearableshavefocusedprimarilyonpulse-echosystems.How-
a limited power consumption. Overall, bringing applications ever, approaches using alternative signal architectures allow
into the unsupervised wearable market requires a whole new to address the unique challenges of wearable ultrasound [47],
level of functional integration and stability to be operated by [121] through shifting the complexity from hardware towards
non-experts. signalprocessing.Techniquessuchasinformationencodingand
3) ComputationandSemanticAbstraction: Unlikehand- on-edge analog or digital signal processing can significantly
held ultrasound systems that focus primarily on raw signal reducepowerconsumptionandminimizethenumberofrequired
capture or imaging [23], [25], [26], [27], wearable ultrasound integratedcomponents[38],[112],[127].Theseapproachesalso
oftendirectlytargetshigher-levelsemanticinformation.Without influencethedesignandintegrationoftransducersinnewways.
a trained operator, who controls the device and interprets the So far, only a few demonstrations or commercial products,
results,thewearablesystemmustdirectlyevaluatephysiological suchasthoseby[35]and[38],haveexploredthesenonpulse-
states[46],[120],healthprediction[49]oruserintentions[3], echoapproachesforspecificapplications.Assuch,webelieve
[69]. The corresponding processing pipeline typically spans thatfutureresearchinthisdirectioncanunlockfurtherpotential
multiple stages: from raw signal and feature processing, to forcompact,lightweightandefficientultrasoundwearables.
theestimationofphysiologicalquantities(e.g.,tissuestiffness,
bloodflowvelocity),anduptotheinferenceofsemantic-level
VI. CONCLUSION
descriptors(seeFig.3).
Systemsthatperformonlybasicsignalconditioningon-edge Wearableultrasoundsensingcanaddressmajorclinical,tech-
and transmit raw data for host processing provide a high level nological, and societal challenges, ranging from personalized
of flexibility [15], [80]. In turn, a high data rate is required healthcareandrehabilitationtoindustrialhuman-machineinter-
which can become a bottle-neck for frame rate and scanned action.Marketprojectionsindicatesustainedgrowth.However,
depth and can consume more power [83]. In this direction, the transition from application-specific requirements, through
this review shows that much of the potential lies in the high laboratoryprototypes,towidelyadoptedproductsremainsdif-
level of integration and smart edge processing [20]. This is ficult. Our assessment of potential applications and their de-
exemplary shown by WULPUS [69], [70], [103]. It produces velopment stages revealed five major challenges that hinder
resultscomparabletothoseofWMAUS[80]butwith22mWit the transition to market-ready products, namely integration,
consumes≈70timeslesspower.TherecentlypublishedPuLsE fragmentation,regulatoryandsafetyconstraints,reliability,and
system[88]alsogoesintothisdirection,showcasingevenless manufacturabilitywithineconomicprofitability.Aboveall,the
power consumption (5.8mW) to drive a complete ultrasound gapisprimarilydefinedbyunresolvedsystem-levelconstraints.
heartratemonitor. Thechallengesofsystemdesignspanmultipledisciplinesand
Computation and semantic abstraction can be considered requirecoordinatedprogressinanalog/digitalICdesign,micro-
as one of the key design challenges for wearable ultrasound machined transducers, low-power signal processing, edge AI,
systems.Itmayoperateinthedomainsofedge,hostandcloud packaging and microsystems engineering, and scalable manu-
processing,butforitskeyrequirementsofweight,powercon- facturing.
sumption,latencyandruntimethemainfocusliesontheedge Basedonthebottlenecks,marketinsights,anticipatedrequire-
processing. Here, the level of edge processing varies from the ments,andthecurrentstateoftheartdiscussedinthisreview,we
mereoutputofrawdata[15],[80],tobeamformeddata[27]and outlineaphasedroadmapforthefuturedevelopmentofwearable
up to physiological data [88], [103]. Interestingly, the power ultrasoundsystems:
consumption of these systems is drastically reduced towards 1)Short-TermPriorities(1to3Years)-FoundationsforCom-
highersemanticinformationprocessingon-edge. parabilityandRapidPrototyping:Thedevelopmentofwearable
4) Interfaces: All analyzed systems in this review used ultrasound systems is currently hindered by the fragmented
available communication interfaces such as USB [27], [38], natureofindividualsolutions.Manyprojectsareforcedtodesign
[107],[112]andethernetICs[80],[89]forthewiredsystemsor custom electronics and system infrastructure from the ground
WiFi[15],[83]andBluetoothICs[35],[36],[88],[103]forthe up [1], [32]. This requirement consumes substantial time and
wirelesssystems.Here,thewirelesscommunicationinterfaces resources and effectively restricts progress to research groups
areparticularlyrelevantforwearables.Systemsthatemployed with expertise in electronic and system design, hindering in-
a Bluetooth interface were able to achieve the lowest power terdisciplinarycollaborationacrossengineering,scientific,and
consumption [88], [103]. Bluetooth has a considerable lower clinical disciplines required for wearable systems [16], [29].

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
| 18  |     |     |     |     |     |     |     |     | IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026 |     |     |     |     |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --------------------------------------------- | --- | --- | --- | --- |
This review showed, that wearable ultrasound systems share be clarified, including thermal and acoustic safety envelopes
considerablecommongroundintheirunderlyingarchitectures, tailoredtowearableoperation.Achievingthesegoalswillmove
indicating that limited availability, re-usability, and flexibility wearable ultrasound devices into TRLs 6 to 7, making them
of existing hardware platforms represent a key bottleneck to suitableforclinicalandindustrialpilotdeployments.
near-term progress. Over the next three years, this challenge 3) Long-Term Vision (7 to 10 Years) - Fully Integrated,
can be addressed by prioritizing shared, open, modular, and Autonomous, and Scalable Wearable Ultrasound Systems: In
reconfigurabledevelopmentplatforms.Theseplatformsshould the long term, wearable ultrasound systems will evolve into
integratefront-endcircuitry,embeddedprocessing,andwireless fully integrated, autonomous platforms capable of continuous
communicationtolowerentrybarriersforapplication-oriented operation in daily life. This will require the development of
teamsandacceleraterapidprototyping,asitwasdemonstrated ultra-low-power system-on-chip solutions that unify analog
with the Modulus platform [113] to develop PuLsE [88]. Fur- front-ends, digital processing, memory, AI accelerators, and
thermore, a platform-based approach enables direct compara- wireless communication into a single, energy-efficient pack-
bilityofresultsacrossdifferentresearcheffortsandallowsfor age. Large-area flexible transducer arrays, enabled by mature
earlyidentificationofsystemrequirementsandsolutions.Asa CMUT/PMUT-on-flextechnologiesandwafer-levelintegration
nextsteptowardshigherintegration,genericresearchplatforms methods,willconformseamlesslytothebodyandenablenew
canactastestbedsformorespecialized,highlyefficientASIC formfactors,includingmultipatchdistributedsensing.Suchsys-
implementations. tems may collaborate wirelessly to achieve synthetic-aperture
Additionally, standardization of interfaces, datasets, and or distributed-beamforming capabilities, enabling imaging or
benchmarking protocols will foster comparability across re- semantic extraction at the system level rather than at a single
search groups and support more systematic design decisions. device.Autonomouson-bodysemanticinferencepipelineswill
Theseeffortsshouldcoversignalquality,energyconsumption, allow devices to directly output physiological states, motion
thermal behavior, and mechanical robustness. At the signal- intentions, or early warning indicators, minimizing data trans-
processing level, preliminary semantic information processing mission and enhancing privacy. These advances will open the
will help reduce data bandwidth and mitigate power demands door to personalized medicine and rehabilitation routines, and
of communication units. In parallel, advances in conformable human-robotcollaboration.Ultimately,thisphasecorresponds
packaging will improve multi-hour stability and user comfort. to TRL 8 to 9, marking the arrival of mature, manufacturable,
Together, these efforts will help elevate current systems from andwidelydeployablewearableultrasoundtechnologies.
earlyproof-of-conceptstagestowardsTRLs4to5. Together, this roadmap shows the critical technological, in-
2)Mid-TermDevelopmentGoals(3to7Years)-Integration, terdisciplinary and infrastructural steps required to transition
Specialization and Regulatory Alignment: Mid-term progress wearable ultrasound from isolated prototypes and proof-of-
will rely on deeper system integration and the emergence of conceptdemonstrationstoscalable,reliableandimpactfulsys-
application-specific architectures. Critical milestones include temsacrosshealthcare,industry,andconsumerdomains.
thedevelopmentofdedicatedultrasoundSIPsorASICsthatinte-
gratetransmit/receivefront-ends,analog-to-digitalconversion,
| beamforming | accelerators, |     | and | low-power |     | control | logic into |     |     |     |     |     |     |
| ----------- | ------------- | --- | --- | --------- | --- | ------- | ---------- | --- | --- | --- | --- | --- | --- |
highlycompactandenergy-efficientpackages.Suchintegration REFERENCES
| will be | necessary | to support |     | scalable | arrays, | higher | channel |     |     |     |     |     |     |
| ------- | --------- | ---------- | --- | -------- | ------- | ------ | ------- | --- | --- | --- | --- | --- | --- |
[1] A.B.Amado-Reyetal.,“Towardsultrasoundwearabletechnologyfor
| counts,     | and more | advanced |     | signal       | architectures. |            | In parallel, |                |             |      |        |             |                   |
| ----------- | -------- | -------- | --- | ------------ | -------------- | ---------- | ------------ | -------------- | ----------- | ---- | ------ | ----------- | ----------------- |
|             |          |          |     |              |                |            |              | cardiovascular | monitoring: | From | device | development | to clinical vali- |
| distributed | sensing  | concepts |     | are expected |                | to emerge, | where        |                |             |      |        |             |                   |
dation,”IEEERev.Biomed.Eng.,vol.18,pp.93–112,2025.[Online].
Available:https://ieeexplore.ieee.org/document/10551463/
| multiple | miniaturized | ultrasound |     | nodes | operate | cooperatively |     |     |     |     |     |     |     |
| -------- | ------------ | ---------- | --- | ----- | ------- | ------------- | --- | --- | --- | --- | --- | --- | --- |
[2] M.X.Renetal.,“Advancementsinflexibleandwearableechocardio-
onthebodyandexchangedataoverhumanbodyareanetworks.
gramsforreal-timecontinuouscardiovascularmonitoring,”Curr.Treat.
| This distributed |     | approach | enables | spatially |     | adaptive | sensing, |     |     |     |     |     |     |
| ---------------- | --- | -------- | ------- | --------- | --- | -------- | -------- | --- | --- | --- | --- | --- | --- |
OptionsCardiovasc.Med.,vol.27,no.1,pp.1–12,Jul.2025.
X.Yangetal.,“Ultrasoundasaneuroroboticinterface:Areview,”IEEE
| reduces | per-node | complexity, |     | and allows |     | computational | load | [3] |     |     |     |     |     |
| ------- | -------- | ----------- | --- | ---------- | --- | ------------- | ---- | --- | --- | --- | --- | --- | --- |
Trans.Syst.,Man,Cybern.,Syst.,vol.54,no.6,pp.3534–3546,Jun.2024.
| to be shared | between | nodes | and | central | hubs. | Tight | coupling |     |     |     |     |     |     |
| ------------ | ------- | ----- | --- | ------- | ----- | ----- | -------- | --- | --- | --- | --- | --- | --- |
[Online].Available:https://ieeexplore.ieee.org/document/10436655/
ofsensing,localpreprocessing,andlow-powercommunication [4] X. Wang et al., “Wearable sensors for activity monitoring and mo-
willbeessentialtomaintainenergyefficiencyandlatencycon- tioncontrol:Areview,”BiomimeticIntell.Robot.,vol.3,no.1,2023,
Art.no.100089,doi:10.1016/j.birob.2023.100089.
| straints. | Hybrid | sensing | approaches |     | that | combine | ultrasound |     |     |     |     |     |     |
| --------- | ------ | ------- | ---------- | --- | ---- | ------- | ---------- | --- | --- | --- | --- | --- | --- |
[5] J.Yangetal.,“Human–machineinteractiontowardsindustry5.0:Human-
with inertial, electrophysiological, or optical modalities will centricsmartmanufacturing,”Digit.Eng.,vol.2,2024,Art.no.100013.
further improve robustness and inference quality, especially [Online]. Available: https://www.sciencedirect.com/science/article/pii/
S2950550X2400013X
in human-machine interaction and physiological monitoring. [6] F. D. Correia et al., “Home-based rehabilitation with a novel digital
Advancesinpackagingandbiocompatiblematerialswillenable biofeedback system versus conventional in-person rehabilitation after
reliable operation over 24 to 72 hours, addressing motion- totalkneereplacement:Afeasibilitystudy,”ScientificReports,vol.8,
no.1,2018,Art.no.11299.
| induced | artifacts, | moisture | exposure, |     | and | long-term | adhesion. |             |                           |     |          |                 |            |
| ------- | ---------- | -------- | --------- | --- | --- | --------- | --------- | ----------- | ------------------------- | --- | -------- | --------------- | ---------- |
|         |            |          |           |     |     |           |           | [7] J. Chen | et al., “Skin-conformable |     | flexible | and stretchable | ultrasound |
Embedded semantic-processing engines based on specialized transducerforwearableimaging,”IEEETrans.Ultrason.,Ferroelectr.,
AI accelerators will allow devices to output intermediate or Freq.Control,vol.71,no.7,pp.811–820,Jul.2024.
[8] K.Mahatoetal.,“Hybridmultimodalwearablesensorsforcomprehen-
| high-level | information |     | rather     | than raw | signals.   | Concurrently, |      |             |              |        |            |         |                    |
| ---------- | ----------- | --- | ---------- | -------- | ---------- | ------------- | ---- | ----------- | ------------ | ------ | ---------- | ------- | ------------------ |
|            |             |     |            |          |            |               |      | sive health | monitoring,” | Nature | Electron., | vol. 7, | no. 9, pp.735–750, |
| regulatory | pathways    | for | continuous |          | ultrasound | exposure      | must |             |              |        |            |         |                    |
2024.

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 19
[9] A.Moinetal.,“Awearablebiosensingsystemwithin-sensoradaptive [32] K.He,“Ultrasound-basedhumanmachineinterfacesforhandgesture
machinelearningforhandgesturerecognition,”NatureElectron.,vol.4, recognition:Ascopingreviewandfuturedirection,”IEEETrans.Med.
no.1,pp.54–63,2021. Robot.Bionics,vol.7,no.1,pp.200–212,Feb.2025.[Online].Available:
[10] R. Jha et al., “Advancements in optical fiber-based wearable sensors https://ieeexplore.ieee.org/document/10816243/
forsmarthealthmonitoring,”BiosensorsBioelectron.,vol.254,2024, [33] X.Xueetal.,“Flexibleultrasonictransducersforwearablebiomedical
Art.no.116232. applications: A review on advanced materials, structural designs, and
[11] C. Wang et al., “Bioadhesive ultrasound for long-term contin- future prospects,” IEEE Trans. Ultrason., Ferroelectr., Freq. Control,
uous imaging of diverse organs,” Science, vol. 377, no. 6605, vol.71,no.7,pp.786–810,Jul.2024.
pp.517–523,2022.[Online].Available:https://www.science.org/doi/10. [34] T.-G. La and L. H. Le, “Flexible and wearable ultrasound device
1126/science.abo2542 for medical applications: A review on materials, structural designs,
[12] A.Omidvaretal.,“FlexiblePolyCMUTs:Fabricationandcharacteri- and current challenges,” Adv. Mater. Technol., vol. 7, no. 3, 2022,
zationofaflexiblepolymer-basedcapacitivemicromachinedultrasonic Art. no. 2100798. [Online]. Available: https://advanced.onlinelibrary.
arrayforconformalultrasonography,”Adv.Mater.Technol.,vol.8,no.5, wiley.com/doi/abs/10.1002/admt.202100798
Art.no.2201316,2023.[Online].Available:https://onlinelibrary.wiley. [35] FlosonicsMedical,“Introducingflowpatch:Hands-freehemodynamic
com/doi/10.1002/admt.202201316 assessmentswithreal-timeresults,”2025.[Online].Available:https://
[13] S. V. Joshi et al., “Flexible micromachined ultrasound transducers flosonicsmedical.com
(MUTs)forbiomedicalapplications,”MicrosystemsNanoeng.,vol.11, [36] Novioscan,“SENS-Ukidsbladdersensorisourfirstproofofwearable
no.1,2025,Art.no.9. ultrasoundcare,”2021.[Online].Available:https://novioscan.com
[14] L.Zhangetal.,“Anemergingera:Conformableultrasoundelectronics,” [37] X. Gao et al., “A wearable echomyography system based on a sin-
Adv.Mater.,vol.36,no.8,2024,Art.no.2307664. gle transducer,” Nature Electron., vol. 7, no. 11, pp.1035–1046,
[15] M.Linetal.,“Afullyintegratedwearableultrasoundsystemtomon- 2024.
itor deep tissues in moving subjects,” Nature Biotechnol., vol. 42, [38] A.Bashatahetal.,“Wearableultrasoundsystemusinglow-voltagetime
no.3,pp.448–457,2024.[Online].Available:https://www.nature.com/ delayspectrometryfordynamictissueimaging,”IEEETrans.Biomed.
articles/s41587-023-01800-0 Eng.,vol.71,no.11,pp.3232–3243,Nov.2024.[Online].Available:
[16] S.Jiangetal.,“Wearableultrasoundbioelectronicsforhealthcaremoni- https://ieeexplore.ieee.org/document/10557691/
toring,”Innovation,vol.4,no.4,2023,Art.no.100447.[Online].Avail- [39] E. Boni et al., “ULA-OP 256: A 256-channel open scanner for de-
able:https://linkinghub.elsevier.com/retrieve/pii/S2666675823000759 velopmentandreal-timeimplementationofnewultrasoundmethods,”
[17] J.M.Rothbergetal.,“Ultrasound-on-chipplatformformedicalimaging, IEEE Trans. Ultrason., Ferroelectr., Freq. Control, vol. 63, no. 10,
analysis, and collective intelligence,” Proc. Nat. Acad. Sci., vol. 118, pp.1488–1495,Oct.2016.
no.27,2021,Art.no.e2019339118.[Online].Available:https://pnas. [40] E.Bonietal.,“Ultrasoundopenplatformsfornext-generationimaging
org/doi/full/10.1073/pnas.2019339118 techniquedevelopment,”IEEETrans.Ultrason.,Ferroelectr.,Freq.Con-
[18] K.KimandH.Choi,“High-efficiencyhigh-voltageclassFamplifierfor trol,vol.65,no.7,pp.1078–1092,Jul.2018.
high-frequencywirelessultrasoundsystems,”PLoSOne,vol.16,no.3, [41] K. Kratkiewicz et al., “Technical considerations in the verasonics
2021,Art.no.e0249034. research ultrasound platform for developing a photoacoustic imag-
[19] Z.Kouetal.,“High-levelsynthesisdesignofscalableultrafastultrasound ing system,” Biomed. Opt. Exp., vol. 12, no. 2, pp.1050–1084,
beamformer with single FPGa,” IEEE Trans. Biomed. Circuits Syst., 2021.
vol.17,no.3,pp.446–457,Jun.2023. [42] D.CackoandM.Lewandowski,“Shearwaveelastographyimplemen-
[20] M. Sinigaglia et al., “Maestro: A 302 GFLOPS/W and 19.8GFLOPS tationonaportableresearchultrasoundsystem:Initialresults,”Appl.
RISC-Vvector-tensorarchitectureforwearableultrasoundedgecom- Sci., vol. 12, no. 12, 2022, Art. no. 6210. [Online]. Available: https:
puting,” IEEE Trans. Circuits Syst. I, Reg. Papers, vol. 72, no. 11, //www.mdpi.com/2076-3417/12/12/6210
pp.6665–6678,Nov.2025. [43] EuropeanCommission,“HorizonEuropeworkprogramme2023-2025,”
[21] C.Choietal.,“Reconfigurableheterogeneousintegrationusingstackable May 2025. [Online]. Available: https://ec.europa.eu/info/funding-
chips with embedded artificial intelligence,” Nature Electron., vol. 5, tenders/opportunities/docs/2021-2027/horizon/wp-call/2023-
no.6,pp.386–393,2022.[Online].Available:https://www.nature.com/ 2024/wp-13-general-annexes_horizon-2023-2024_en.pdf
articles/s41928-022-00778-y [44] YoleGroup,“Marketandtechnologytrends:Sensorsandacuatorsfor
[22] A.K.etal.,“AI-poweredwristultrasoundforperipheralarterialdisease,” wearables,”Jan.2025.[Online].Available:https://www.yolegroup.com/
in Proc. 2nd Int. Conf. Intell. Cyber Phys. Syst. Internet of Things, product/report/sensors-and-actuators-for-wearables-2025/
2024, pp.1630–1634. [Online]. Available: https://ieeexplore.ieee.org/ [45] L.-w.H.Lehmanetal.,“Methodsofbloodpressuremeasurementinthe
document/10695998/ ICU,”Crit.CareMed.,vol.41,no.1,pp.34–40,Jan.2013.[Online].
[23] S.p.A.EsaoteMylabx90productbrochure,Jan.2025.[Online].Avail- Available:http://journals.lww.com/00003246-201301000-00005
able: https://www2.esaote.com/ultrasound/ultrasound-system/mylab- [46] S. Zhou et al., “Clinical validation of a wearable ultrasound sensor
x90/ of blood pressure,” Nature Biomed. Eng., vol. 9, pp.865–881, 2025.
[24] GE Healthcare Technologies Inc, “Versana premierTM prod- [Online]. Available: https://www.nature.com/articles/s41551-024-
uct brochure,” Aug. 2024. [Online]. Available: https://gehealthcare- 01279-3
ultrasound.com/en/versana-family/versana-premiertm/ [47] J.-É. S. Kenny et al., “A wireless wearable Doppler ultrasound de-
[25] Butterfly Network Inc, “iQ3 Ultrasound - the clear answer in tectschangingstrokevolume:Proof-of-principlecomparisonwithtrans-
point-of-care ultrasound,” 2025. [Online]. Available: https://www. esophagealechocardiographyduringcoronarybypasssurgery,”Bioengi-
butterflynetwork.com/iq3 neering, vol. 8, no. 12, Dec. 2021, Art. no. 203. [Online]. Available:
[26] GE Healthcare Technologies Inc, “Vscan airTM - wireless handheld https://www.mdpi.com/2306-5354/8/12/203
ultrasound,”2025.[Online].Available:https://vscan.rocks/de [48] F. Wang et al., “Flexible Doppler ultrasound device for the moni-
[27] VermonSA,“VersatileoemUSBultrasoundprobes,”2024.[Online]. toring of blood flow velocity,” Sci. Adv., vol. 7, no. 44, Oct. 2021,
Available:https://vermon.com/oem-usb-probe/ Art.no.eabi9283.[Online].Available:https://www.science.org/doi/10.
[28] X.Xuetal.,“Aprogrammableplatformforacceleratingthedevelopment 1126/sciadv.abi9283
of smart ultrasound transducer probe,” IEEE Trans. Ultrason., Ferro- [49] H.Huetal.,“Awearablecardiacultrasoundimager,”Nature,vol.613,
electr.,Freq.Control,vol.68,no.4,pp.1296–1304,Apr.2021. no.7945,pp.667–675,2023.[Online].Available:https://www.nature.
[29] P.Songetal.,“Clinical,safety,andengineeringperspectivesonwearable com/articles/s41586-022-05498-z
ultrasoundtechnology:Areview,”IEEETrans.Ultrason.,Ferroelectr., [50] PulsifyMedical,“Ultrasoundcardiacmonitoring,”2025.[Online].Avail-
Freq.Control,vol.71,no.7,pp.730–744,Jul.2024.[Online].Available: able:https://pulsify-medical.com/product/
https://ieeexplore.ieee.org/document/10356100/ [51] E.Georgitzikisetal.,“78-2:Aflat-panel-displaycompatibleultrasound
[30] H. Huang et al., “Emerging wearable ultrasound technology,” IEEE platform,”inProc.SIDSymp.Dig.Techn.Papers,Jun.2023,vol.54,
Trans.Ultrason.,Ferroelectr.,Freq.Control,vol.71,no.7,pp.713–729, no.1,pp.1101–1104.[Online].Available:https://sid.onlinelibrary.wiley.
Jul. 2024. [Online]. Available: https://ieeexplore.ieee.org/document/ com/doi/10.1002/sdtp.16764
10296510/ [52] GE HealthCare, “Novii patch-system,” Apr. 2025. [Online]. Avail-
[31] S.Zhouetal.,“Wearableultrasoundtechnology,”NatureRev.Bioeng., able: https://www.gehealthcare.de/products/maternal-infant-care/fetal-
vol.3,pp.835–854,2025. monitors/novii-wireless-patch-system

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
20 IEEEREVIEWSINBIOMEDICALENGINEERING,VOL.0,2026
[53] H. Harrison et al., “A systematic review comparing surveillance rec- [74] S.Moonetal.,“Aflexibleandwearablesparseultrasoundarrayintegrated
ommendationsforthedetectionofrecurrencefollowingsurgeryacross with a functional electrical stimulation array for spatially distributed
16 common cancer types,” BMJ Oncol., vol. 4, no. 1, Mar. 2025, sequential stimulation,” in Proc. 2024 IEEE Ultrasonics, Ferroelect„
Art. no. e000627. [Online]. Available: https://bmjoncology.bmj.com/ Freq.ControlJointSymp.,Taipei,Taiwan,Sep.2024,pp.1–4.[Online].
lookup/doi/10.1136/bmjonc-2024-000627 Available:https://ieeexplore.ieee.org/document/10793707/
[54] K.M.K.Leadinghametal.,“Designofacustomflexibleultrasound [75] E. L. King et al., “Distributed wearable ultrasound sensors predict
transducerasanimplantablecranialsensorforlong-termpost-operative isometricgroundreactionforce,”Sensors,vol.24,no.15,Aug.2024,
monitoring of brain tumor regrowth,” in Proc. IEEE Int. Ultrasonics Art.no.5023.[Online].Available:https://www.mdpi.com/1424-8220/
Symp.,Oct.2022,pp.1–4.[Online].Available:https://ieeexplore.ieee. 24/15/5023
org/document/9958345 [76] P.-Z.Lyuetal.,“Howpareticandnon-pareticanklemusclescontract
[55] S. J. Pietrangelo et al., “A wearable transcranial Doppler ultrasound duringwalkinginstrokesurvivors:Newinsightusingnovelwearable
phasedarraysystem,”inProc.IntracranialPress.NeuromonitoringXVI, ultrasoundimagingandsensingtechnology,”Biosensors,vol.12,no.5,
2018,pp.111–114. May 2022, Art. no. 349. [Online]. Available: https://www.mdpi.com/
[56] S.Zhouetal.,“Transcranialvolumetricimagingusingaconformalultra- 2079-6374/12/5/349
soundpatch,”Nature,vol.629,no.8013,pp.810–818,May2024.[On- [77] I.AlMohimeedandY.Ono,“Ultrasoundmeasurementofskeletalmuscle
line].Available:https://www.nature.com/articles/s41586-024-07381-5 contractileparametersusingflexibleandwearablesingle-elementultra-
[57] J.Huanetal.,“Awearabledual-modeprobeforimage-guidedclosed- sonicsensor,”Sensors,vol.20,no.13,Jun.2020,Art.no.3616.[Online].
loopultrasoundneuromodulation,”IEEETrans.Biomed.CircuitsSyst., Available:https://www.mdpi.com/1424-8220/20/13/3616
vol. 19, no. 2, pp.357–373, Apr. 2025. [Online]. Available: https: [78] X. Xue et al., “Advancing quadriceps muscle monitoring: Wearable
//ieeexplore.ieee.org/document/10596042 a-modeultrasoundandmachinelearningclassificationforaccuratees-
[58] H.-C.Liuetal.,“Wearablebioadhesiveultrasoundshearwaveelastog- timationofmusclestates,”inProc.2023IEEEInt.UltrasonicsSymp.,
raphy,” Sci. Adv., vol. 10, no. 6, 2024, Art. no. eadk 8426. [Online]. Montreal,QC,Canada,Sep.2023,pp.1–4.[Online].Available:https:
Available:https://www.science.org/doi/10.1126/sciadv.adk8426 //ieeexplore.ieee.org/document/10307406/
[59] K.Tranetal.,“LungslidingdetectioninM-modeusingwearableul- [79] T.L.Szabo,DiagnosticUltrasoundImaging:InsideOut,2nded.Boston,
trasonicsensor:Anin-vivofeasibilitystudy,”inProc.2023IEEEInt. MA,USA:AcademicPress,2014.
UltrasonicsSymp.,Montreal,QC,Canada,Sep.2023,pp.1–4.[Online]. [80] X. Yang et al., “A wearable ultrasound system for sensing muscular
Available:https://ieeexplore.ieee.org/document/10307019/ morphologicaldeformations,”IEEETrans.Syst.,Man,Cybern.,Syst.,
[60] W. Du et al., “Conformable ultrasound breast patch for deep tis- vol. 51, no. 6, pp.3370–3379, Jun. 2021. [Online]. Available: https:
sue scanning and imaging,” Sci. Adv., vol. 9, no. 30, Jul. 2023, //ieeexplore.ieee.org/document/8760415/
Art.no.eadh5325.[Online].Available:https://www.science.org/doi/10. [81] G.Montaldoetal.,“Coherentplane-wavecompoundingforveryhigh
1126/sciadv.adh5325 frame rate ultrasonography and transient elastography,” IEEE Trans.
[61] S. Hofstetter et al., “DFree ultrasonic sensor in supporting quality of Ultrason., Ferroelectr., Freq. Control, vol. 56, no. 3, pp.489–506,
lifeandpatientsatisfactionwithbladderdysfunction,”Int.J.Urological Mar.2009.
Nurs.,vol.17,no.1,pp.62–69,2023. [82] H.HasegawaandH.Kanai,“High-frame-rateechocardiographywithre-
[62] DFreeInc,“DFree-wearablebladderscannerforincontinence,”2024. ducedsidelobelevel,”IEEETrans.Ultrason.,Ferroelectr.,Freq.Control,
[Online].Available:https://www.dfreeus.biz vol.59,no.11,pp.2569–2575,Nov.2012.
[63] Verathon Inc, “BladderScan BVI 6100: Product information,” 2021. [83] S. Vostrikov et al., “TinyProbe: A wearable 32-channel multimodal
[Online].Available:https://www.verathon.com/sites/default/files/2021- wirelessultrasoundprobe,”IEEETrans.Ultrason.,Ferroelectr.,Freq.
10/0900-1078_Rev-12_BladderScan_BVI6100_Brochure_WEB.pdf Control,vol.72,no.1,pp.64–76,Jan.2025.[Online].Available:https:
[64] X.Yangetal.,“ComparativeanalysisofwearableA-modeultrasound //ieeexplore.ieee.org/document/10750870/
andsEMGformuscle-computerinterface,”IEEETrans.Bio-Med.Eng., [84] R.Manwaretal.,“Overviewofultrasounddetectiontechnologiesforpho-
vol.67,no.9,pp.2434–2442,Sep.2020.[Online].Available:https:// toacousticimaging,”Micromachines,vol.11,no.7,2020,Art.no.692.
ieeexplore.ieee.org/document/8943971/ [Online].Available:https://www.mdpi.com/2072-666X/11/7/692
[65] A.GolardandS.S.Talathi,“Ultrasoundforgazeestimation—Amodel- [85] E.Moiselloetal.,“PMUTandCMUTdevicesforbiomedicalapplica-
ingandempiricalstudy,”Sensors,vol.21,no.13,Jun.2021,Art.no.4502. tions:Areview,”IEEEAccess,vol.12,pp.18640–18657,2024.
[Online].Available:https://www.mdpi.com/1424-8220/21/13/4502 [86] O. Oralkan et al., “High-frequency CMUT arrays for high-resolution
[66] B. G. Sgambato et al., “High performance wearable ultrasound as a medical imaging,” in Proc. IEEE Ultrasonics Symp., 2004, vol. 1,
human-machineinterfaceforwristandhandkinematictracking,”IEEE pp.399–402.
Trans.Biomed.Eng.,vol.71,no.2,pp.484–493,Feb.2024.[Online]. [87] M.Giordanoetal.,“Towardsanovelultrasoundsystembasedonlow-
Available:https://ieeexplore.ieee.org/document/10227550/ frequencyfeatureextractionfromafully-printedflexibletransducer,”in
[67] X.Yangetal.,“Self-supervisedlearningforintuitivecontrolofprosthetic Proc.2023IEEEBiomed.CircuitsSyst.Conf.,2023,pp.1–5.
handmovements via sonomyography,”IEEE Trans. Cybern., vol. 55, [88] M.Giordanoetal.,“PuLsE:Accurateandrobustultrasound-basedcon-
no. 1, pp.409–420, Jan. 2025. [Online]. Available: https://ieeexplore. tinuousheart-ratemonitoringonawrist-wornIoTdevice,”IEEEInternet
ieee.org/document/10752584/ ThingsJ.,vol.12,no.18,pp.36908–36925,Sep.2025.
[68] Z. Yin et al., “A wearable multisensor fusion system for neuropros- [89] Z. Yin et al., “A wearable ultrasound interface for prosthetic hand
thetic hand,” IEEE Sensors J., vol. 25, no. 8, pp.12547–12558, Apr. control,”IEEEJ.Biomed.HealthInform.,vol.26,no.11,pp.5384–5393,
2025. Nov. 2022. [Online]. Available: https://ieeexplore.ieee.org/document/
[69] S.Vostrikovetal.,“Unsupervisedfeatureextractionfromrawdatafor 9872106/
gesture recognition with wearable ultralow-power ultrasound,” IEEE [90] “Aium official statement for recommended maximum scanning times
Trans.Ultrasonics,Ferroelect.,Freq.Control,vol.71,no.7,pp.831–841, fordisplayedthermalindexvalues,”J.UltrasoundMed.,vol.42,no.12,
Jul. 2024. [Online]. Available: https://ieeexplore.ieee.org/document/ pp.E74–E75,2023.[Online].Available:https://onlinelibrary.wiley.com/
10538295/ doi/abs/10.1002/jum.16322
[70] G. Spacone et al., “Tracking of wrist and hand kinematics with ultra [91] F.Ling,SynchronizationinDigitalCommunicationSystems,J.Proakis,
lowpowerwearableA-modeultrasound,”IEEETrans.Biomed.Circuits Ed. Cambridge, U.K.: Cambridge Univ. Press, 2017. [Online].
Syst.,vol.19,no.3,pp.536–548,Jun.2025.[Online].Available:https: Available: https://www.cambridge.org/ch/universitypress/subjects/
//ieeexplore.ieee.org/document/10685090/ engineering/communications-and-signal-processing/synchronization-
[71] Q.Zengyuetal.,“Asimultaneousgestureclassificationandforceestima- digital-communication-systems?format=HB&isbn=9781107114739
tionstrategybasedonwearableA-modeultrasoundandcascademodel,” [92] P.G.vanLeuterenetal.,“SENS-U:Validationofawearableultrasonic
IEEETrans.NeuralSyst.Rehabil.Eng.,vol.30,pp.2301–2311,2022. bladdermonitorinchildrenduringurodynamicstudies,”J.Pediatr.Urol.,
[Online].Available:https://ieeexplore.ieee.org/document/9851659/ vol.14,no.6,pp.569.e1–569.e6,2018.
[72] Q. Shangguan et al., “DANN-Repositing strategy for zero retraining [93] X. Yang et al., “A proportional pattern recognition control scheme
long-termhandgesturerecognitionusingwearableA-modeultrasound,” forwearableA-modeultrasoundsensing,”IEEETrans.Ind.Electron.,
IEEETrans.Instrum.Meas.,vol.73,2024,Art.no.2530711.[Online]. vol. 67, no. 1, pp.800–808, Jan. 2020. [Online]. Available: https://
Available:https://ieeexplore.ieee.org/document/10680560/ ieeexplore.ieee.org/document/8654210/
[73] S. Vostrikov et al., “A muscle pennation angle estimation framework [94] X.Yangetal.,“Simultaneouspredictionofwrist/handmotionviawear-
from raw ultrasound data for wearable biomedical instrumentation,” ableultrasoundsensing,”IEEETrans.NeuralSyst.Rehabil.Eng.,vol.28,
IEEETrans.Instrumen.Meas.,vol.73,2024,Art.no.2501712.[Online]. no.4,pp.970–977,Apr.2020.[Online].Available:https://ieeexplore.
Available:https://ieeexplore.ieee.org/document/10329945/ ieee.org/document/9020139/

This article has been accepted for inclusion in a future issue of this journal. Content is final as presented, with the exception of pagination.
WEIKetal.:CURRENTTRENDSINULTRASOUNDWEARABLES:SPOTLIGHTONSYSTEMARCHITECTURE 21
[95] X.Yangetal.,“Wearableultrasound-baseddecodingofsimultaneous [116] R.W.Nuckolsetal.,“Individualizationofexosuitassistancebasedon
wrist/hand kinematics,” IEEE Trans. Ind. Electron., vol. 68, no. 9, measuredmuscledynamicsduringversatilewalking,”Sci.Robot.,vol.6,
pp.8667–8675,Sep.2021.[Online].Available:https://ieeexplore.ieee. no.60,2021,Art.no.eabj1362.[Online].Available:https://www.science.
org/document/9185023/ org/doi/abs/10.1126/scirobotics.abj1362
[96] L. Guo et al., “A gesture recognition strategy based on A-mode ul- [117] A.Pullinietal.,“Mr.Wolf:Anenergy-precisionscalableparallelultra
trasoundforidentifyingknownandunknowngestures,”IEEESensors lowpowerSoCforIoTedgeprocessing,”IEEEJ.Solid-StateCircuits,
J., vol. 22, no. 11, pp.10730–10739, Jun. 2022. [Online]. Available: vol.54,no.7,pp.1970–1981,Jul.2019.
https://ieeexplore.ieee.org/document/9760285/ [118] M. Ali et al., “Signal processing overview of ultrasound systems for
[97] Z.Luetal.,“Wearablereal-timegesturerecognitionschemebasedon medicalimaging,”SPRAB12,TexasInstruments,Texas,vol.55,2008.
A-modeultrasound,”IEEETrans.NeuralSyst.Rehabil.Eng.,vol.30, Jan.10,2026.[Online].Available:https://www.ti.com/lit/wp/sprab12/
pp.2623–2629,2022. sprab12.pdf?ts=1771582700856
[98] D. Liu et al., “Dynamic hand gesture recognition based on A-mode [119] J.-É. S. Kenny et al., “A carotid Doppler patch accurately tracks
ultrasoundsensing:Proposinganalgorithmbasedonthelongshort-term stroke volume changes during a preload-modifying maneuver in
memory framework,” IEEE Syst., Man, Cybern. Mag., vol. 9, no. 4, healthy volunteers,” Crit. Care Explorations, vol. 2, no. 1, 2020,
pp.45–52,Oct.2023. Art.no.e0072.[Online].Available:https://journals.lww.com/10.1097/
[99] J. Zeng et al., “Adaptive learning against muscle fatigue for A-mode CCE.0000000000000072
ultrasound-based gesture recognition,” IEEE Trans. Instrum. Meas., [120] J.-É. S. Kenny, “Functional hemodynamic monitoring with a wire-
vol.72,2023,Art.no.4009810.[Online].Available:https://ieeexplore. lessultrasoundpatch,”J.CardiothoracicVasc.Anesth.,vol.35,no.5,
ieee.org/document/10208224/ pp.1509–1515, 2021. [Online]. Available: https://www.sciencedirect.
[100] S.Weietal.,“Amultimodalmultilevelconvergedattentionnetworkfor com/science/article/pii/S105307702100077X
handgesturerecognitionwithhybridsEMGandA-modeultrasoundsens- [121] C.Mundingetal.,“Invitroandclinicaldemonstrationofrelativevelocity
ing,”IEEETrans.Cybern.,vol.53,no.12,pp.7723–7734,Dec.2023. measurements with the FlopatchTM: A wearable Doppler ultrasound
[Online].Available:https://ieeexplore.ieee.org/document/9901457/ patch,”inProc.2021IEEEInt.UltrasonicsSymp.,Sep.2021,pp.1–4.
[101] E.Ltd,“Elonxiultrasonicsignalcollector,”2023.[Online].Available: [Online].Available:https://ieeexplore.ieee.org/document/9593456
http://elonxi.cn/?list_40/73.html [122] J. K. Eibl et al., “Systems and methods for automated fluid
[102] Z. Yin et al., “Wearable ultrasound interface for prosthetic hand response measurement,” Patent U.S. 20180353154A1. [Online].
manipulation,” in Proc. 15th Int. Conf. Intell. Robot. Appl., 2022, Available: https://patents.google.com/patent/US20180353154A1/
pp.3–12.[Online].Available:https://link.springer.com/10.1007/978-3- en?oq=US20180353154A1
031-13835-5_1 [123] A.Yazdkhastietal.,“Anovelconceptofanacousticultrasoundwearable
[103] S.Freyetal.,“WULPUS:Awearableultralow-powerultrasoundprobe forearlydetectionofimplantfailure,”Sci.Rep.,vol.14,no.1,2024,
formulti-daymonitoringofcarotidarteryandmuscleactivity,”inProc. Art.no.31326,doi:10.1038/s41598-024-82743-7.
2022 IEEE Int. Ultrasonics Symp., Venice, Italy, Oct. 2022, pp.1–4. [124] T. Misaridis and J. Jensen, “Use of modulated excitation signals in
[Online].Available:https://ieeexplore.ieee.org/document/9958156/ medicalultrasound.PartI:Basicconceptsandexpectedbenefits,”IEEE
[104] S.Vostrikovetal.,“Completecardiorespiratorymonitoringviawearable Trans.Ultrason.,Ferroelectr.,Freq.Control,vol.52,no.2,pp.177–191,
ultralowpowerultrasound,”inProc.2023IEEEInt.UltrasonicsSymp., Feb. 2005. [Online]. Available: https://ieeexplore.ieee.org/document/
Montreal,QC,Canada,Sep.2023,pp.1–4.[Online].Available:https: 1406545/
//ieeexplore.ieee.org/document/10307398/ [125] C. Weng et al., “Coded excitation for ultrasonic testing: A review,”
[105] S.Freyetal.,“Awearableultra-low-powersEMG-triggeredultrasound Sensors,vol.24,no.7,2024,Art.no.2167.[Online].Available:https:
systemforlong-termmuscleactivitymonitoring,”inProc.2023IEEEInt. //www.mdpi.com/1424-8220/24/7/2167
UltrasonicsSymp.,Montreal,QC,Canada,Sep.2023,pp.1–4.[Online]. [126] J.Koberetal.,“MiniaturizedultrasonictransducerwithPMN-PTem-
Available:https://ieeexplore.ieee.org/document/10307824/ beddedintoflexibleLCPsubstrateforbiocompatibleapplications,”IEEE
[106] S.Vostrikovetal.,“WULPUS-wearableultralow-powerultrasound,” Open J. Ultrasonics, Ferroelectr., Freq. Control, vol. 5, pp.269–275,
GitHubRepository,2025.[Online].Available:https://github.com/pulp- 2025.
bio/wulpus [127] M. Han and C. Yoon, “Efficient pulse compression using Barker
[107] M. Fournelle et al., “Portable ultrasound research system for use in coded excitation and mismatched filter for portable ultrasound sys-
automatedbladdermonitoringwithmachine-learning-basedsegmenta- tem,” J. Acoustical Soc. Korea, vol. 44, no. 1, pp.49–57, 2025, doi:
tion,”Sensors,vol.21,no.19,2021,Art.no.6481.[Online].Available: 10.7776/ASK.2025.44.1.049.
https://www.mdpi.com/1424-8220/21/19/6481 [128] T. Choi et al., “Golay-coded excitations for rotational intravascular
[108] B.G.Sgambatoetal.,“Towardsnaturalmulti-DoFprostheticcontrolwith ultrasound imaging,” IEEE Access, vol. 7, pp.119718–119728, 2019.
distributed ultrasound,” in Proc. 2024 IEEE Ultrasonics, Ferroelectr., [Online].Available:https://ieeexplore.ieee.org/document/8807182
Freq.ControlJointSymp.,2024,pp.1–6.[Online].Available:https:// [129] X.Wangetal.,“Researchongolay-codedexcitationinreal-timeimag-
ieeexplore.ieee.org/document/10793502/ ing of high frequency ultrasound biomicroscopy,” Sci. Rep., vol. 11,
[109] S. Vostrikov et al., “TinyProbe - A wearable 32-channel multi-modal no.1,2021,Art.no.1848.[Online].Available:https://www.nature.com/
wirelessultrasoundprobe,”GitHubRepository,2025.[Online].Avail- articles/s41598-020-80406-x
able:https://github.com/pulp-bio/TinyProbe [130] C.Challinoretal.,“CodedexcitationusingTOP-CSsequencesformulti-
[110] U.S.FoodandDrugAdministration,“Premarketnotification[510(k)] channellow-powerultrasonics,”Mech.Syst.Signal.Process.,vol.213,
summary:K222242FloPatchFP120,”2022.[Online].Available:https: 2024,Art.no.111339.[Online].Available:https://www.sciencedirect.
//www.accessdata.fda.gov/cdrh_docs/pdf22/K222242.pdf com/science/article/pii/S0888327024002371
[111] J.-É. S. Kenny et al., “A novel, hands-free ultrasound patch for con- [131] J.T.Alvarezetal.,“Stimulation-inducedmuscledeformationmeasured
tinuousmonitoringofquantitativeDopplerinthecarotidartery,”Sci. with a-mode ultrasound correlates with muscle fatigue,” IEEE Trans.
Rep., vol. 11, no. 1, 2021, Art. no. 7780. [Online]. Available: https: NeuralSyst.Rehabil.Eng.,vol.33,pp.10–21,2025.
//www.nature.com/articles/s41598-021-87116-y [132] L.Zhangetal.,“Aconformablephased-arrayultrasoundpatchforbladder
[112] J.Wangetal.,“Apre-voidingalarmsystemusingwearableultrasound volumemonitoring,”NatureElectron.,vol.7,no.1,pp.77–90,2024.
andmachinelearningalgorithmsforchildrenwithnocturnalenuresis,” [133] P.L.vanNeeretal.,“Flexiblelarge-areaultrasoundarraysformedicalap-
IEEEJ.Transl.Eng.HealthMed.,vol.12,pp.643–658,2024.[Online]. plicationsmadeusingembossedpolymerstructures,”NatureCommun.,
Available:https://ieeexplore.ieee.org/document/10671589/ vol.15,no.1,2024,Art.no.2802.
[113] C. Leitner et al., “Modulus: A sandbox for high-resolution wearable [134] D.-H.Kangetal.,“Siliconnanocolumn-baseddisposableandflexible
ultrasounddevelopment,”inProc.2025IEEEInt.UltrasonicsSymp., ultrasoundpatches,”NatureCommun.,vol.16,no.1,2025,Art.no.6609.
2025,pp.1–4. [135] J.Lietal.,“Body-coupledpowertransmissionandenergyharvesting,”
[114] S. Lin et al., “Effect of RUSI-based core stability exercise on NatureElectron.,vol.4,no.7,pp.530–538,2021.
chronic non-specific low back pain patients: Study protocol for a [136] X.Gaoetal.,“Ultrasoundimagingwithflexibletransducersbasedon
randomised controlled trial,” BMJ Open, vol. 11, no. 12, 2021, real-time and high-accuracy shape estimation,” Ultrasonics, vol. 148,
Art.no.e047317. 2025,Art.no.107551.[Online].Available:https://www.sciencedirect.
[115] Z.-H.Huangetal.,“Real-timevisualbiofeedbackviawearableultra- com/science/article/pii/S0041624X24003147
soundimagingcanenhancethemusclecontractiontrainingoutcomeof [137] W.Chenetal.,“Flexibleultrasoundtransducerwithembeddedoptical
youngadults,”J.StrengthConditioningRes.,vol.36,no.4,pp.941–947, shapesensingfiberforbiomedicalimagingapplications,”IEEETrans.
Apr.2022. Biomed.Eng.,vol.70,no.10,pp.2841–2851,Oct.2023.