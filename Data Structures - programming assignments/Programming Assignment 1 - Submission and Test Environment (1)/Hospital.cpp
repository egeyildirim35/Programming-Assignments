#include "Hospital.h"

#include <cassert>

std::ostream& operator<<(std::ostream& s, const EventResult& r)
{
    int enumIndex = (r.type < 0 || r.type > InvalidEvent) ? InvalidEvent : r.type;
    s << "Time[" << r.timePoint << "]: ";
    switch(enumIndex)
    {
        case DoctorQueueCheck:
            s << "Doctor(" << r.patientIdOrDoctorIndex
              << ") checked the patient queue." << std::endl;
            break;
        case RegistrationQueueEntrance:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") " << "is registering." << std::endl;
            break;
        case RegistrationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") registeration is complete." << std::endl;
            break;
        case ExaminationEnd:
            s << "Patient(" << r.patientIdOrDoctorIndex
              << ") examination is completed." << std::endl;
            break;
        case InvalidEvent:
        default:
            s << "Invalid Event!" << std::endl;
            break;
    }

    return s;
}

int Doctor::ExamTimeOf(const Patient& patient) const
{
    int pri_lvl = patient.getPriority();
    int r;
    r = (MAX_PATIENT_PRIORTIY-pri_lvl+1)*baselineExaminationTime;
    // TODO: Implement
    return r;
}


Hospital::Hospital(const Doctor& d0,
                   const Doctor& d1,
                   int rTime, int docTime)
    : currentTime(0)
    , registrationTime(rTime)
    , doctorCheckTime(docTime)
{
    doctors[0] = d0;
    doctors[1] = d1;
    patientsInExam[0] = NULL;
    patientsInExam[1] = NULL;
    
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 0));
    eventQueue.InsertItem(new Event(currentTime + doctorCheckTime, DoctorQueueCheck, 1));
}

Hospital::~Hospital()
{
    while(!(regQueue.is_empty()))
    {
        Patient* patient = regQueue.Dequeue();
        delete patient;
    }
    if(patientsInExam[0]!=NULL)
    {
        delete patientsInExam[0];
        patientsInExam[0] = NULL;
    }
    if(patientsInExam[1]!=NULL)
    {
        delete patientsInExam[1];
        patientsInExam[1] = NULL;
    }
    while (!eventQueue.IsEmpty()) 
    {
        Event* event = eventQueue.RemoveFirstItem();
        delete event;
    }
    // TODO: Implement
}

void Hospital::AddPatient(int id, int priority)
{
    if(priority>MAX_PATIENT_PRIORTIY)
    {
        return;
    }
    Patient *new_pati = new Patient(id,priority);
    regQueue.Enqueue(new_pati);
    
    Event *reg_event = new Event(currentTime,RegistrationQueueEntrance,new_pati);
    eventQueue.InsertItem(reg_event);
    // TODO: Implement
}

EventResult Hospital::DoSingleEventIteration()
{
    
    if(eventQueue.IsEmpty())
    {
        return EventResult();
    }
    
    Event * curr_event = eventQueue.RemoveFirstItem();
    
    EventResult result;
    result.type = (*curr_event).getType();
    currentTime = (*curr_event).getTimePoint();
    result.timePoint = currentTime;
    
    
    if((*curr_event).getType()==RegistrationQueueEntrance)
    {
        const Patient* pati =(*curr_event).getPatient();
        result.patientIdOrDoctorIndex = pati->getId();
        Event* register_end = new Event(currentTime + registrationTime, RegistrationEnd, pati);
        eventQueue.InsertItem(register_end);
    }
    
    else if((*curr_event).getType()==RegistrationEnd)
    {
        const Patient* pati =(*curr_event).getPatient();
        result.patientIdOrDoctorIndex = pati->getId();
        
        Patient* pati_to_exam = regQueue.Dequeue();
        examQueue.InsertItemPrior(pati_to_exam);
    }
    
    else if((*curr_event).getType()==DoctorQueueCheck)
    {
        int doc_index = (*curr_event).getDoctorIndex();
        result.patientIdOrDoctorIndex = doc_index;
        if(patientsInExam[doc_index]==NULL && !examQueue.IsEmpty())
        {
            Patient* pati = examQueue.RemoveFirstItem();
            patientsInExam[doc_index] = pati;
            
            Event* exam_end = new Event(currentTime + (doctors[doc_index]).ExamTimeOf(*pati), ExaminationEnd, pati);
            eventQueue.InsertItem(exam_end);
        }
        else
        {
            Event* doc_check = new Event(currentTime + doctorCheckTime, DoctorQueueCheck, doc_index);
            eventQueue.InsertItem(doc_check);
        }
    }
    
    else if ((*curr_event).getType() == ExaminationEnd) {
        const Patient* pati = curr_event->getPatient();
        result.patientIdOrDoctorIndex = pati->getId();
        int doc_index;
        if(patientsInExam[0] == pati)
        {
            doc_index = 0;
        }
        else if((patientsInExam[1] == pati))
        {
            doc_index = 1;
        }
        else
        {
            return EventResult();
        }

        delete patientsInExam[doc_index];
        patientsInExam[doc_index] = NULL;

        if (!examQueue.IsEmpty()) {
            Patient* nextPatient = examQueue.RemoveFirstItem();
            patientsInExam[doc_index] = nextPatient;

            int examTime = doctors[doc_index].ExamTimeOf(*nextPatient);
            Event* examEndEvent = new Event(currentTime + examTime,ExaminationEnd,nextPatient);
            eventQueue.InsertItem(examEndEvent);
        } else {
            Event* nextCheckEvent = new Event(currentTime + doctorCheckTime,DoctorQueueCheck,doc_index);
            eventQueue.InsertItem(nextCheckEvent);
        }
    }
    else if((*curr_event).getType()==InvalidEvent)
    {
        return EventResult();
    }
    
    // TODO: Implement
    delete curr_event;
    return result;
}
