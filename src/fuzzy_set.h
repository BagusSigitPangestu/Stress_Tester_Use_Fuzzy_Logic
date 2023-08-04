void fuzzySet()
{
  // FuzzyInput
  FuzzyInput *PHR = new FuzzyInput(1);

  PHR->addFuzzySet(Lambat);
  PHR->addFuzzySet(Normal);
  PHR->addFuzzySet(AgakCepat);
  PHR->addFuzzySet(Cepat);
  fuzzy->addFuzzyInput(PHR);

  // FuzzyInput
  FuzzyInput *GSR = new FuzzyInput(2);

  GSR->addFuzzySet(Kecil);
  GSR->addFuzzySet(Sedang);
  GSR->addFuzzySet(Besar);
  GSR->addFuzzySet(SangatBesar);
  fuzzy->addFuzzyInput(GSR);

  // FuzzyInput
  FuzzyInput *Suhu = new FuzzyInput(3);

  Suhu->addFuzzySet(SangatDingin);
  Suhu->addFuzzySet(Dingin);
  Suhu->addFuzzySet(AgakDingin);
  Suhu->addFuzzySet(Normal1);
  fuzzy->addFuzzyInput(Suhu);

  // FuzzyOutput
  FuzzyOutput *TingkatSress = new FuzzyOutput(1);

  TingkatSress->addFuzzySet(Rileks);
  TingkatSress->addFuzzySet(Tenang);
  TingkatSress->addFuzzySet(Cemas);
  TingkatSress->addFuzzySet(Stress);
  fuzzy->addFuzzyOutput(TingkatSress);
}

void fuzzyRule()
{
  // Building FuzzyRule 1
  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_1->joinWithAND(Lambat, Kecil);

  FuzzyRuleAntecedent *SUHUnormal_1 = new FuzzyRuleAntecedent();
  SUHUnormal_1->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_1AndSUHUnormal_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_1AndSUHUnormal_1->joinWithAND(PHRlambatAndGSRkecil_1, SUHUnormal_1);

  FuzzyRuleConsequent *thenTingkatStressRileks_1 = new FuzzyRuleConsequent();
  thenTingkatStressRileks_1->addOutput(Rileks);

  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, PHRlambatAndGSRkecil_1AndSUHUnormal_1, thenTingkatStressRileks_1);
  fuzzy->addFuzzyRule(fuzzyRule1);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 2
  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_2 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_2->joinWithAND(Lambat, Kecil);

  FuzzyRuleAntecedent *SUHUagakDigin_1 = new FuzzyRuleAntecedent();
  SUHUagakDigin_1->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_2AndSUHUagakDigin_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_2AndSUHUagakDigin_1->joinWithAND(PHRlambatAndGSRkecil_2, SUHUagakDigin_1);

  FuzzyRuleConsequent *thenTingkatStressRileks_2 = new FuzzyRuleConsequent();
  thenTingkatStressRileks_2->addOutput(Rileks);

  FuzzyRule *fuzzyRule2 = new FuzzyRule(1, PHRlambatAndGSRkecil_2AndSUHUagakDigin_1, thenTingkatStressRileks_2);
  fuzzy->addFuzzyRule(fuzzyRule2);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 3
  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_3 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_3->joinWithAND(Lambat, Kecil);

  FuzzyRuleAntecedent *SUHUdingin_1 = new FuzzyRuleAntecedent();
  SUHUdingin_1->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_3AndSUHUdingin_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_3AndSUHUdingin_1->joinWithAND(PHRlambatAndGSRkecil_3, SUHUdingin_1);

  FuzzyRuleConsequent *thenTingkatStressTenang_1 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_1->addOutput(Tenang);

  FuzzyRule *fuzzyRule3 = new FuzzyRule(1, PHRlambatAndGSRkecil_3AndSUHUdingin_1, thenTingkatStressTenang_1);
  fuzzy->addFuzzyRule(fuzzyRule3);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 4
  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_4 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_4->joinWithAND(Lambat, Kecil);

  FuzzyRuleAntecedent *SUHUsangatDingin_1 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_1->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRkecil_4AndSUHUsangatDingin_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRkecil_4AndSUHUsangatDingin_1->joinWithAND(PHRlambatAndGSRkecil_4, SUHUsangatDingin_1);

  FuzzyRuleConsequent *thenTingkatStressCemas_1 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_1->addOutput(Cemas);

  FuzzyRule *fuzzyRule4 = new FuzzyRule(1, PHRlambatAndGSRkecil_4AndSUHUsangatDingin_1, thenTingkatStressCemas_1);
  fuzzy->addFuzzyRule(fuzzyRule4);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 5
  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_1 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_1->joinWithAND(Normal, Kecil);

  FuzzyRuleAntecedent *SUHUnormal_2 = new FuzzyRuleAntecedent();
  SUHUnormal_2->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_1AndSUHUnormal_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_1AndSUHUnormal_2->joinWithAND(PHRnormalAndGSRkecil_1, SUHUnormal_2);

  FuzzyRuleConsequent *thenTingkatStressRileks_3 = new FuzzyRuleConsequent();
  thenTingkatStressRileks_3->addOutput(Rileks);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(1, PHRnormalAndGSRkecil_1AndSUHUnormal_2, thenTingkatStressRileks_3);
  fuzzy->addFuzzyRule(fuzzyRule5);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 6
  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_2->joinWithAND(Lambat, Kecil);

  FuzzyRuleAntecedent *SUHUagakDingin_2 = new FuzzyRuleAntecedent();
  SUHUagakDingin_2->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_2AndSUHUagakDingin_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_2AndSUHUagakDingin_2->joinWithAND(PHRnormalAndGSRkecil_2, SUHUagakDingin_2);

  FuzzyRuleConsequent *thenTingkatStressTenang_2 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_2->addOutput(Tenang);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(1, PHRnormalAndGSRkecil_2AndSUHUagakDingin_2, thenTingkatStressTenang_2);
  fuzzy->addFuzzyRule(fuzzyRule6);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 7
  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_3 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_3->joinWithAND(Normal, Kecil);

  FuzzyRuleAntecedent *SUHUdingin_2 = new FuzzyRuleAntecedent();
  SUHUdingin_2->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_3AndSUHUdingin_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_3AndSUHUdingin_2->joinWithAND(PHRnormalAndGSRkecil_3, SUHUdingin_2);

  FuzzyRuleConsequent *thenTingkatStressTenang_3 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_3->addOutput(Tenang);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(1, PHRnormalAndGSRkecil_3AndSUHUdingin_2, thenTingkatStressTenang_3);
  fuzzy->addFuzzyRule(fuzzyRule7);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 8
  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_4 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_4->joinWithAND(Normal, Kecil);

  FuzzyRuleAntecedent *SUHUsangatDingin_2 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_2->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRkecil_4AndSUHUsangatDingin_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRkecil_4AndSUHUsangatDingin_2->joinWithAND(PHRnormalAndGSRkecil_4, SUHUsangatDingin_2);

  FuzzyRuleConsequent *thenTingkatStressCemas_2 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_2->addOutput(Cemas);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(1, PHRnormalAndGSRkecil_4AndSUHUsangatDingin_2, thenTingkatStressCemas_2);
  fuzzy->addFuzzyRule(fuzzyRule8);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 9
  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_1 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_1->joinWithAND(AgakCepat, Kecil);

  FuzzyRuleAntecedent *SUHUnormal_3 = new FuzzyRuleAntecedent();
  SUHUnormal_3->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_1AndSUHUnormal_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_1AndSUHUnormal_3->joinWithAND(PHRagakCepatAndGSRkecil_1, SUHUnormal_3);

  FuzzyRuleConsequent *thenTingkatStressTenang_4 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_4->addOutput(Tenang);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(1, PHRagakCepatAndGSRkecil_1AndSUHUnormal_3, thenTingkatStressTenang_4);
  fuzzy->addFuzzyRule(fuzzyRule9);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 10
  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_2 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_2->joinWithAND(AgakCepat, Kecil);

  FuzzyRuleAntecedent *SUHUagakDingin_3 = new FuzzyRuleAntecedent();
  SUHUagakDingin_3->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_2AndSUHUagakDingin_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_2AndSUHUagakDingin_3->joinWithAND(PHRagakCepatAndGSRkecil_2, SUHUagakDingin_3);

  FuzzyRuleConsequent *thenTingkatStressTenang_5 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_5->addOutput(Tenang);

  FuzzyRule *fuzzyRule10 = new FuzzyRule(1, PHRagakCepatAndGSRkecil_2AndSUHUagakDingin_3, thenTingkatStressTenang_5);
  fuzzy->addFuzzyRule(fuzzyRule10);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 11
  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_3->joinWithAND(AgakCepat, Kecil);

  FuzzyRuleAntecedent *SUHUdingin_3 = new FuzzyRuleAntecedent();
  SUHUdingin_3->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_3AndSUHUdingin_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_3AndSUHUdingin_3->joinWithAND(PHRlambatAndGSRkecil_1, SUHUdingin_3);

  FuzzyRuleConsequent *thenTingkatStressCemas_3 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_3->addOutput(Cemas);

  FuzzyRule *fuzzyRule11 = new FuzzyRule(1, PHRagakCepatAndGSRkecil_3AndSUHUdingin_3, thenTingkatStressCemas_3);
  fuzzy->addFuzzyRule(fuzzyRule11);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 12
  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_4 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_3->joinWithAND(AgakCepat, Kecil);

  FuzzyRuleAntecedent *SUHUsangatDingin_3 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_3->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRkecil_4AndSUHUsangatDingin_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRkecil_4AndSUHUsangatDingin_3->joinWithAND(PHRagakCepatAndGSRkecil_4, SUHUsangatDingin_3);

  FuzzyRuleConsequent *thenTingkatStressCemas_4 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_4->addOutput(Cemas);

  FuzzyRule *fuzzyRule12 = new FuzzyRule(1, PHRagakCepatAndGSRkecil_4AndSUHUsangatDingin_3, thenTingkatStressCemas_4);
  fuzzy->addFuzzyRule(fuzzyRule12);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 13
  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_1 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_1->joinWithAND(Cepat, Kecil);

  FuzzyRuleAntecedent *SUHUnormal_4 = new FuzzyRuleAntecedent();
  SUHUnormal_4->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_1AndSUHUnormal_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_1AndSUHUnormal_4->joinWithAND(PHRcepatAndGSRkecil_1, SUHUnormal_4);

  FuzzyRuleConsequent *thenTingkatStressTenang_6 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_6->addOutput(Tenang);

  FuzzyRule *fuzzyRule13 = new FuzzyRule(1, PHRcepatAndGSRkecil_1AndSUHUnormal_4, thenTingkatStressTenang_6);
  fuzzy->addFuzzyRule(fuzzyRule13);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 14
  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_2 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_2->joinWithAND(Cepat, Kecil);

  FuzzyRuleAntecedent *SUHUagakDingin_4 = new FuzzyRuleAntecedent();
  SUHUagakDingin_4->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_2AndSUHUagakDingin_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_2AndSUHUagakDingin_4->joinWithAND(PHRcepatAndGSRkecil_2, SUHUagakDingin_4);

  FuzzyRuleConsequent *thenTingkatStressTenang_7 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_7->addOutput(Tenang);

  FuzzyRule *fuzzyRule14 = new FuzzyRule(1, PHRcepatAndGSRkecil_2AndSUHUagakDingin_4, thenTingkatStressTenang_7);
  fuzzy->addFuzzyRule(fuzzyRule14);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 15
  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_3 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_3->joinWithAND(Cepat, Kecil);

  FuzzyRuleAntecedent *SUHUdingin_4 = new FuzzyRuleAntecedent();
  SUHUdingin_4->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_3AndSUHUdingin_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_3AndSUHUdingin_4->joinWithAND(PHRcepatAndGSRkecil_3, SUHUdingin_4);

  FuzzyRuleConsequent *thenTingkatStressCemas_5 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_5->addOutput(Cemas);

  FuzzyRule *fuzzyRule15 = new FuzzyRule(1, PHRcepatAndGSRkecil_3AndSUHUdingin_4, thenTingkatStressCemas_5);
  fuzzy->addFuzzyRule(fuzzyRule15);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 16
  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_4->joinWithAND(Cepat, Kecil);

  FuzzyRuleAntecedent *SUHUsangatDingin_4 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_4->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRkecil_4AndSUHUsangatDingin_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRkecil_4AndSUHUsangatDingin_4->joinWithAND(PHRcepatAndGSRkecil_4, SUHUsangatDingin_4);

  FuzzyRuleConsequent *thenTingkatStressCemas_6 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_6->addOutput(Cemas);

  FuzzyRule *fuzzyRule16 = new FuzzyRule(1, PHRcepatAndGSRkecil_4AndSUHUsangatDingin_4, thenTingkatStressCemas_6);
  fuzzy->addFuzzyRule(fuzzyRule16);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 17
  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_1 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_1->joinWithAND(Lambat, Sedang);

  FuzzyRuleAntecedent *SUHUnormal_5 = new FuzzyRuleAntecedent();
  SUHUnormal_5->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_1AndSUHUnormal_5 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_1AndSUHUnormal_5->joinWithAND(PHRLambatAndGSRsedang_1, SUHUnormal_5);

  FuzzyRuleConsequent *thenTingkatStressRileks_4 = new FuzzyRuleConsequent();
  thenTingkatStressRileks_4->addOutput(Rileks);

  FuzzyRule *fuzzyRule17 = new FuzzyRule(1, PHRLambatAndGSRsedang_1AndSUHUnormal_5, thenTingkatStressRileks_4);
  fuzzy->addFuzzyRule(fuzzyRule17);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 18
  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_2 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_2->joinWithAND(Lambat, Sedang);

  FuzzyRuleAntecedent *SUHUagakDingin_5 = new FuzzyRuleAntecedent();
  SUHUagakDingin_5->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_2AndSUHUagakDingin_5 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_2AndSUHUagakDingin_5->joinWithAND(PHRLambatAndGSRsedang_2, SUHUagakDingin_5);

  FuzzyRuleConsequent *thenTingkatStressTenang_8 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_8->addOutput(Tenang);

  FuzzyRule *fuzzyRule18 = new FuzzyRule(1, PHRLambatAndGSRsedang_2AndSUHUagakDingin_5, thenTingkatStressTenang_8);
  fuzzy->addFuzzyRule(fuzzyRule18);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 19
  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_3 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_3->joinWithAND(Lambat, Sedang);

  FuzzyRuleAntecedent *SUHUdingin_5 = new FuzzyRuleAntecedent();
  SUHUdingin_5->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_3AndSUHUdingin_5 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_3AndSUHUdingin_5->joinWithAND(PHRLambatAndGSRsedang_3, SUHUdingin_5);

  FuzzyRuleConsequent *thenTingkatStressTenang_9 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_9->addOutput(Tenang);

  FuzzyRule *fuzzyRule19 = new FuzzyRule(1, PHRLambatAndGSRsedang_3AndSUHUdingin_5, thenTingkatStressTenang_9);
  fuzzy->addFuzzyRule(fuzzyRule19);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 20
  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_4 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_4->joinWithAND(Lambat, Sedang);

  FuzzyRuleAntecedent *SUHUsangatDingin_5 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_5->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRLambatAndGSRsedang_4AndSUHUsangatDingin_5 = new FuzzyRuleAntecedent();
  PHRLambatAndGSRsedang_4AndSUHUsangatDingin_5->joinWithAND(PHRLambatAndGSRsedang_4, SUHUsangatDingin_5);

  FuzzyRuleConsequent *thenTingkatStressCemas_7 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_7->addOutput(Cemas);

  FuzzyRule *fuzzyRule20 = new FuzzyRule(1, PHRLambatAndGSRsedang_4AndSUHUsangatDingin_5, thenTingkatStressCemas_7);
  fuzzy->addFuzzyRule(fuzzyRule20);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 21
  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_1 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_1->joinWithAND(Normal, Sedang);

  FuzzyRuleAntecedent *SUHUnormal_6 = new FuzzyRuleAntecedent();
  SUHUnormal_6->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_1AndSUHUnormal_6 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_1AndSUHUnormal_6->joinWithAND(PHRNormalAndGSRsedang_1, SUHUnormal_6);

  FuzzyRuleConsequent *thenTingkatStressTenang_10 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_10->addOutput(Tenang);

  FuzzyRule *fuzzyRule21 = new FuzzyRule(1, PHRNormalAndGSRsedang_1AndSUHUnormal_6, thenTingkatStressTenang_10);
  fuzzy->addFuzzyRule(fuzzyRule21);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 22
  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_2 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_2->joinWithAND(Normal, Sedang);

  FuzzyRuleAntecedent *SUHUagakDingin_6 = new FuzzyRuleAntecedent();
  SUHUagakDingin_6->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_2AndSUHUagakDingin_6 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_2AndSUHUagakDingin_6->joinWithAND(PHRNormalAndGSRsedang_2, SUHUagakDingin_6);

  FuzzyRuleConsequent *thenTingkatStressTenang_11 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_11->addOutput(Tenang);

  FuzzyRule *fuzzyRule22 = new FuzzyRule(1, PHRNormalAndGSRsedang_2AndSUHUagakDingin_6, thenTingkatStressTenang_11);
  fuzzy->addFuzzyRule(fuzzyRule22);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 23
  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_3 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_3->joinWithAND(Normal, Sedang);

  FuzzyRuleAntecedent *SUHUdingin_6 = new FuzzyRuleAntecedent();
  SUHUdingin_6->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_3AndSUHUdingin_6 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_3AndSUHUdingin_6->joinWithAND(PHRNormalAndGSRsedang_3, SUHUdingin_6);

  FuzzyRuleConsequent *thenTingkatStressTenang_12 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_12->addOutput(Tenang);

  FuzzyRule *fuzzyRule23 = new FuzzyRule(1, PHRNormalAndGSRsedang_3AndSUHUdingin_6, thenTingkatStressTenang_12);
  fuzzy->addFuzzyRule(fuzzyRule23);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 24
  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_4 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_4->joinWithAND(Normal, Sedang);

  FuzzyRuleAntecedent *SUHUsangatDingin_6 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_6->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRNormalAndGSRsedang_4AndSUHUsangatDingin_6 = new FuzzyRuleAntecedent();
  PHRNormalAndGSRsedang_4AndSUHUsangatDingin_6->joinWithAND(PHRNormalAndGSRsedang_4, SUHUsangatDingin_6);

  FuzzyRuleConsequent *thenTingkatStressCemas_8 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_8->addOutput(Cemas);

  FuzzyRule *fuzzyRule24 = new FuzzyRule(1, PHRNormalAndGSRsedang_4AndSUHUsangatDingin_6, thenTingkatStressCemas_8);
  fuzzy->addFuzzyRule(fuzzyRule24);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 25
  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_1 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_1->joinWithAND(AgakCepat, Sedang);

  FuzzyRuleAntecedent *SUHUnormal_7 = new FuzzyRuleAntecedent();
  SUHUnormal_7->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_1AndSUHUnormal_7 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_1AndSUHUnormal_7->joinWithAND(PHRAgakCepatAndGSRsedang_1, SUHUnormal_7);

  FuzzyRuleConsequent *thenTingkatStressCemas_9 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_9->addOutput(Cemas);

  FuzzyRule *fuzzyRule25 = new FuzzyRule(1, PHRAgakCepatAndGSRsedang_1AndSUHUnormal_7, thenTingkatStressCemas_9);
  fuzzy->addFuzzyRule(fuzzyRule25);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 26
  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_2 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_2->joinWithAND(AgakCepat, Sedang);

  FuzzyRuleAntecedent *SUHUagakDingin_7 = new FuzzyRuleAntecedent();
  SUHUagakDingin_7->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_2AndSUHUagakDingin_7 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_2AndSUHUagakDingin_7->joinWithAND(PHRAgakCepatAndGSRsedang_2, SUHUagakDingin_7);

  FuzzyRuleConsequent *thenTingkatStressCemas_10 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_10->addOutput(Cemas);

  FuzzyRule *fuzzyRule26 = new FuzzyRule(1, PHRAgakCepatAndGSRsedang_2AndSUHUagakDingin_7, thenTingkatStressCemas_10);
  fuzzy->addFuzzyRule(fuzzyRule26);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 27
  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_3 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_3->joinWithAND(AgakCepat, Sedang);

  FuzzyRuleAntecedent *SUHUdingin_7 = new FuzzyRuleAntecedent();
  SUHUdingin_7->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_3AndSUHUdingin_7 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_3AndSUHUdingin_7->joinWithAND(PHRAgakCepatAndGSRsedang_3, SUHUdingin_7);

  FuzzyRuleConsequent *thenTingkatStressCemas_11 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_11->addOutput(Cemas);

  FuzzyRule *fuzzyRule27 = new FuzzyRule(1, PHRAgakCepatAndGSRsedang_3AndSUHUdingin_7, thenTingkatStressCemas_11);
  fuzzy->addFuzzyRule(fuzzyRule27);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 28
  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_4 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_4->joinWithAND(AgakCepat, Sedang);

  FuzzyRuleAntecedent *SUHUsangatDingin_7 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_7->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRAgakCepatAndGSRsedang_4AndSUHUsangatDingin_7 = new FuzzyRuleAntecedent();
  PHRAgakCepatAndGSRsedang_4AndSUHUsangatDingin_7->joinWithAND(PHRAgakCepatAndGSRsedang_4, SUHUsangatDingin_7);

  FuzzyRuleConsequent *thenTingkatStressCemas_12 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_12->addOutput(Cemas);

  FuzzyRule *fuzzyRule28 = new FuzzyRule(1, PHRAgakCepatAndGSRsedang_4AndSUHUsangatDingin_7, thenTingkatStressCemas_12);
  fuzzy->addFuzzyRule(fuzzyRule28);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 29
  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_1 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_1->joinWithAND(Cepat, Sedang);

  FuzzyRuleAntecedent *SUHUnormal_8 = new FuzzyRuleAntecedent();
  SUHUnormal_8->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_1AndSUHUnormal_8 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_1AndSUHUnormal_8->joinWithAND(PHRCepatAndGSRsedang_1, SUHUnormal_8);

  FuzzyRuleConsequent *thenTingkatStressTenang_13 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_13->addOutput(Tenang);

  FuzzyRule *fuzzyRule29 = new FuzzyRule(1, PHRCepatAndGSRsedang_1AndSUHUnormal_8, thenTingkatStressTenang_13);
  fuzzy->addFuzzyRule(fuzzyRule29);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 30
  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_2 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_2->joinWithAND(Cepat, Sedang);

  FuzzyRuleAntecedent *SUHUagakDingin_8 = new FuzzyRuleAntecedent();
  SUHUagakDingin_8->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_2AndSUHUagakDingin_8 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_2AndSUHUagakDingin_8->joinWithAND(PHRCepatAndGSRsedang_2, SUHUagakDingin_8);

  FuzzyRuleConsequent *thenTingkatStressCemas_13 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_13->addOutput(Cemas);

  FuzzyRule *fuzzyRule30 = new FuzzyRule(1, PHRCepatAndGSRsedang_2AndSUHUagakDingin_8, thenTingkatStressCemas_13);
  fuzzy->addFuzzyRule(fuzzyRule30);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 31
  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_3 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_3->joinWithAND(Cepat, Sedang);

  FuzzyRuleAntecedent *SUHUdingin_8 = new FuzzyRuleAntecedent();
  SUHUdingin_8->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_3AndSUHUdingin_8 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_3AndSUHUdingin_8->joinWithAND(PHRCepatAndGSRsedang_3, SUHUdingin_8);

  FuzzyRuleConsequent *thenTingkatStressCemas_14 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_14->addOutput(Cemas);

  FuzzyRule *fuzzyRule31 = new FuzzyRule(1, PHRCepatAndGSRsedang_3AndSUHUdingin_8, thenTingkatStressCemas_14);
  fuzzy->addFuzzyRule(fuzzyRule31);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 32
  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_4 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_4->joinWithAND(Cepat, Sedang);

  FuzzyRuleAntecedent *SUHUsangatDingin_8 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_8->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRCepatAndGSRsedang_4AndSUHUsangatDingin_8 = new FuzzyRuleAntecedent();
  PHRCepatAndGSRsedang_4AndSUHUsangatDingin_8->joinWithAND(PHRCepatAndGSRsedang_4, SUHUsangatDingin_8);

  FuzzyRuleConsequent *thenTingkatStressCemas_15 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_15->addOutput(Cemas);

  FuzzyRule *fuzzyRule32 = new FuzzyRule(1, PHRCepatAndGSRsedang_4AndSUHUsangatDingin_8, thenTingkatStressCemas_15);
  fuzzy->addFuzzyRule(fuzzyRule32);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 33
  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_1->joinWithAND(Lambat, Besar);

  FuzzyRuleAntecedent *SUHUnormal_9 = new FuzzyRuleAntecedent();
  SUHUnormal_9->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_1AndSUHUnormal_9 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_1AndSUHUnormal_9->joinWithAND(PHRlambatAndGSRbesar_1, SUHUnormal_9);

  FuzzyRuleConsequent *thenTingkatStressTenang_14 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_14->addOutput(Tenang);

  FuzzyRule *fuzzyRule33 = new FuzzyRule(1, PHRlambatAndGSRbesar_1AndSUHUnormal_9, thenTingkatStressTenang_14);
  fuzzy->addFuzzyRule(fuzzyRule33);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 34
  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_2 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_2->joinWithAND(Lambat, Besar);

  FuzzyRuleAntecedent *SUHUagakDingin_9 = new FuzzyRuleAntecedent();
  SUHUagakDingin_9->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_2AndSUHUagakDingin_9 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_2AndSUHUagakDingin_9->joinWithAND(PHRlambatAndGSRbesar_2, SUHUagakDingin_9);

  FuzzyRuleConsequent *thenTingkatStressTenang_15 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_15->addOutput(Tenang);

  FuzzyRule *fuzzyRule34 = new FuzzyRule(1, PHRlambatAndGSRbesar_2AndSUHUagakDingin_9, thenTingkatStressTenang_15);
  fuzzy->addFuzzyRule(fuzzyRule34);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 35
  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_3 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_3->joinWithAND(Lambat, Besar);

  FuzzyRuleAntecedent *SUHUdingin_9 = new FuzzyRuleAntecedent();
  SUHUdingin_9->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_3AndSUHUdingin_9 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_3AndSUHUdingin_9->joinWithAND(PHRlambatAndGSRbesar_3, SUHUdingin_9);

  FuzzyRuleConsequent *thenTingkatStressCemas_16 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_16->addOutput(Cemas);

  FuzzyRule *fuzzyRule35 = new FuzzyRule(1, PHRlambatAndGSRbesar_3AndSUHUdingin_9, thenTingkatStressCemas_16);
  fuzzy->addFuzzyRule(fuzzyRule35);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 36
  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_4 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_4->joinWithAND(Lambat, Besar);

  FuzzyRuleAntecedent *SUHUsangatDingin_9 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_9->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRbesar_4AndSUHUsangatDingin_9 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRbesar_4AndSUHUsangatDingin_9->joinWithAND(PHRlambatAndGSRbesar_4, SUHUsangatDingin_9);

  FuzzyRuleConsequent *thenTingkatStressCemas_17 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_17->addOutput(Cemas);

  FuzzyRule *fuzzyRule36 = new FuzzyRule(1, PHRlambatAndGSRbesar_4AndSUHUsangatDingin_9, thenTingkatStressCemas_17);
  fuzzy->addFuzzyRule(fuzzyRule36);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 37
  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_1 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_1->joinWithAND(Normal, Besar);

  FuzzyRuleAntecedent *SUHUnormal_10 = new FuzzyRuleAntecedent();
  SUHUnormal_10->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_1AndSUHUnormal_10 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_1AndSUHUnormal_10->joinWithAND(PHRnormalAndGSRbesar_1, SUHUnormal_10);

  FuzzyRuleConsequent *thenTingkatStressTenang_16 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_16->addOutput(Tenang);

  FuzzyRule *fuzzyRule37 = new FuzzyRule(1, PHRnormalAndGSRbesar_1AndSUHUnormal_10, thenTingkatStressTenang_16);
  fuzzy->addFuzzyRule(fuzzyRule37);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 38
  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_2->joinWithAND(Normal, Besar);

  FuzzyRuleAntecedent *SUHUagakDingin_10 = new FuzzyRuleAntecedent();
  SUHUagakDingin_10->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_2AndSUHUagakDingin_10 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_2AndSUHUagakDingin_10->joinWithAND(PHRnormalAndGSRbesar_2, SUHUagakDingin_10);

  FuzzyRuleConsequent *thenTingkatStressTenang_17 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_17->addOutput(Tenang);

  FuzzyRule *fuzzyRule38 = new FuzzyRule(1, PHRnormalAndGSRbesar_2AndSUHUagakDingin_10, thenTingkatStressTenang_17);
  fuzzy->addFuzzyRule(fuzzyRule38);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 39
  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_3 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_3->joinWithAND(Normal, Besar);

  FuzzyRuleAntecedent *SUHUdingin_10 = new FuzzyRuleAntecedent();
  SUHUdingin_10->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_3AndSUHUdingin_10 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_3AndSUHUdingin_10->joinWithAND(PHRnormalAndGSRbesar_3, SUHUdingin_10);

  FuzzyRuleConsequent *thenTingkatStressCemas_18 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_18->addOutput(Cemas);

  FuzzyRule *fuzzyRule39 = new FuzzyRule(1, PHRnormalAndGSRbesar_3AndSUHUdingin_10, thenTingkatStressCemas_18);
  fuzzy->addFuzzyRule(fuzzyRule39);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 40
  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_4 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_4->joinWithAND(Normal, Besar);

  FuzzyRuleAntecedent *SUHUsangatDingin_10 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_10->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRbesar_4AndSUHUsangatDingin_10 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRbesar_4AndSUHUsangatDingin_10->joinWithAND(PHRnormalAndGSRbesar_4, SUHUsangatDingin_10);

  FuzzyRuleConsequent *thenTingkatStressCemas_19 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_19->addOutput(Cemas);

  FuzzyRule *fuzzyRule40 = new FuzzyRule(1, PHRnormalAndGSRbesar_4AndSUHUsangatDingin_10, thenTingkatStressCemas_19);
  fuzzy->addFuzzyRule(fuzzyRule40);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 41
  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_1 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_1->joinWithAND(AgakCepat, Besar);

  FuzzyRuleAntecedent *SUHUnormal_11 = new FuzzyRuleAntecedent();
  SUHUnormal_11->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_1AndSUHUnormal_11 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_1AndSUHUnormal_11->joinWithAND(PHRagakCepatAndGSRbesar_1, SUHUnormal_11);

  FuzzyRuleConsequent *thenTingkatStressCemas_20 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_20->addOutput(Cemas);

  FuzzyRule *fuzzyRule41 = new FuzzyRule(1, PHRagakCepatAndGSRbesar_1AndSUHUnormal_11, thenTingkatStressCemas_20);
  fuzzy->addFuzzyRule(fuzzyRule41);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 42
  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_2 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_2->joinWithAND(AgakCepat, Besar);

  FuzzyRuleAntecedent *SUHUagakDingin_11 = new FuzzyRuleAntecedent();
  SUHUagakDingin_11->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_2AndSUHUagakDingin_11 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_2AndSUHUagakDingin_11->joinWithAND(PHRagakCepatAndGSRbesar_2, SUHUagakDingin_11);

  FuzzyRuleConsequent *thenTingkatStressCemas_21 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_21->addOutput(Cemas);

  FuzzyRule *fuzzyRule42 = new FuzzyRule(1, PHRagakCepatAndGSRbesar_2AndSUHUagakDingin_11, thenTingkatStressCemas_21);
  fuzzy->addFuzzyRule(fuzzyRule42);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 43
  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_3->joinWithAND(AgakCepat, Besar);

  FuzzyRuleAntecedent *SUHUdingin_11 = new FuzzyRuleAntecedent();
  SUHUdingin_11->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_3AndSUHUdingin_11 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_3AndSUHUdingin_11->joinWithAND(PHRagakCepatAndGSRbesar_3, SUHUdingin_11);

  FuzzyRuleConsequent *thenTingkatStressCemas_22 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_22->addOutput(Cemas);

  FuzzyRule *fuzzyRule43 = new FuzzyRule(1, PHRagakCepatAndGSRbesar_3AndSUHUdingin_11, thenTingkatStressCemas_22);
  fuzzy->addFuzzyRule(fuzzyRule43);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 44
  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_4 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_4->joinWithAND(AgakCepat, Besar);

  FuzzyRuleAntecedent *SUHUsangatDingin_11 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_11->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRbesar_4AndSUHUsangatDingin_11 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRbesar_4AndSUHUsangatDingin_11->joinWithAND(PHRagakCepatAndGSRbesar_4, SUHUsangatDingin_11);

  FuzzyRuleConsequent *thenTingkatStressCemas_23 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_23->addOutput(Cemas);

  FuzzyRule *fuzzyRule44 = new FuzzyRule(1, PHRagakCepatAndGSRbesar_4AndSUHUsangatDingin_11, thenTingkatStressCemas_23);
  fuzzy->addFuzzyRule(fuzzyRule44);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 45
  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_1 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_1->joinWithAND(Cepat, Besar);

  FuzzyRuleAntecedent *SUHUnormal_12 = new FuzzyRuleAntecedent();
  SUHUnormal_12->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_1AndSUHUnormal_12 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_1AndSUHUnormal_12->joinWithAND(PHRcepatAndGSRbesar_1, SUHUnormal_12);

  FuzzyRuleConsequent *thenTingkatStressCemas_24 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_24->addOutput(Cemas);

  FuzzyRule *fuzzyRule45 = new FuzzyRule(1, PHRcepatAndGSRbesar_1AndSUHUnormal_12, thenTingkatStressCemas_24);
  fuzzy->addFuzzyRule(fuzzyRule45);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 46
  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_2 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_2->joinWithAND(Cepat, Besar);

  FuzzyRuleAntecedent *SUHUagakDingin_12 = new FuzzyRuleAntecedent();
  SUHUagakDingin_12->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_2AndSUHUagakDingin_12 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_2AndSUHUagakDingin_12->joinWithAND(PHRcepatAndGSRbesar_2, SUHUagakDingin_12);

  FuzzyRuleConsequent *thenTingkatStressCemas_25 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_25->addOutput(Cemas);

  FuzzyRule *fuzzyRule46 = new FuzzyRule(1, PHRcepatAndGSRbesar_2AndSUHUagakDingin_12, thenTingkatStressCemas_25);
  fuzzy->addFuzzyRule(fuzzyRule46);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 47
  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_3 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_3->joinWithAND(Cepat, Besar);

  FuzzyRuleAntecedent *SUHUdingin_12 = new FuzzyRuleAntecedent();
  SUHUdingin_12->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_3AndSUHUdingin_12 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_3AndSUHUdingin_12->joinWithAND(PHRcepatAndGSRbesar_3, SUHUdingin_12);

  FuzzyRuleConsequent *thenTingkatStressCemas_26 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_26->addOutput(Cemas);

  FuzzyRule *fuzzyRule47 = new FuzzyRule(1, PHRcepatAndGSRbesar_3AndSUHUdingin_12, thenTingkatStressCemas_26);
  fuzzy->addFuzzyRule(fuzzyRule47);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 48
  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_4->joinWithAND(Cepat, Besar);

  FuzzyRuleAntecedent *SUHUsangatDingin_12 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_12->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRbesar_4AndSUHUsangatDingin_12 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRbesar_4AndSUHUsangatDingin_12->joinWithAND(PHRcepatAndGSRbesar_4, SUHUsangatDingin_12);

  FuzzyRuleConsequent *thenTingkatStressStress_1 = new FuzzyRuleConsequent();
  thenTingkatStressStress_1->addOutput(Stress);

  FuzzyRule *fuzzyRule48 = new FuzzyRule(1, PHRcepatAndGSRbesar_4AndSUHUsangatDingin_12, thenTingkatStressStress_1);
  fuzzy->addFuzzyRule(fuzzyRule48);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 49
  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_1 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_1->joinWithAND(Lambat, SangatBesar);

  FuzzyRuleAntecedent *SUHUnormal_13 = new FuzzyRuleAntecedent();
  SUHUnormal_13->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_1AndSUHUnormal_13 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_1AndSUHUnormal_13->joinWithAND(PHRlambatAndGSRsangatBesar_1, SUHUnormal_13);

  FuzzyRuleConsequent *thenTingkatStressTenang_18 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_18->addOutput(Tenang);

  FuzzyRule *fuzzyRule49 = new FuzzyRule(1, PHRlambatAndGSRsangatBesar_1AndSUHUnormal_13, thenTingkatStressTenang_18);
  fuzzy->addFuzzyRule(fuzzyRule49);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 50
  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_2 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_2->joinWithAND(Lambat, SangatBesar);

  FuzzyRuleAntecedent *SUHUagakDingin_13 = new FuzzyRuleAntecedent();
  SUHUagakDingin_13->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_2AndSUHUagakDingin_13 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_2AndSUHUagakDingin_13->joinWithAND(PHRlambatAndGSRsangatBesar_2, SUHUagakDingin_13);

  FuzzyRuleConsequent *thenTingkatStressTenang_19 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_19->addOutput(Tenang);

  FuzzyRule *fuzzyRule50 = new FuzzyRule(1, PHRlambatAndGSRsangatBesar_2AndSUHUagakDingin_13, thenTingkatStressTenang_19);
  fuzzy->addFuzzyRule(fuzzyRule50);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 51
  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_3 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_3->joinWithAND(Lambat, SangatBesar);

  FuzzyRuleAntecedent *SUHUdingin_13 = new FuzzyRuleAntecedent();
  SUHUdingin_13->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_3AndSUHUdingin_13 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_3AndSUHUdingin_13->joinWithAND(PHRlambatAndGSRsangatBesar_3, SUHUdingin_13);

  FuzzyRuleConsequent *thenTingkatStressCemas_27 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_27->addOutput(Cemas);

  FuzzyRule *fuzzyRule51 = new FuzzyRule(1, PHRlambatAndGSRsangatBesar_3AndSUHUdingin_13, thenTingkatStressCemas_27);
  fuzzy->addFuzzyRule(fuzzyRule51);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 52
  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_4 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_4->joinWithAND(Lambat, SangatBesar);

  FuzzyRuleAntecedent *SUHUsangatDingin_13 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_13->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRlambatAndGSRsangatBesar_4AndSUHUsangatDingin_13 = new FuzzyRuleAntecedent();
  PHRlambatAndGSRsangatBesar_4AndSUHUsangatDingin_13->joinWithAND(PHRlambatAndGSRsangatBesar_4, SUHUsangatDingin_13);

  FuzzyRuleConsequent *thenTingkatStressCemas_28 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_28->addOutput(Cemas);

  FuzzyRule *fuzzyRule52 = new FuzzyRule(1, PHRlambatAndGSRsangatBesar_4AndSUHUsangatDingin_13, thenTingkatStressCemas_28);
  fuzzy->addFuzzyRule(fuzzyRule52);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 53
  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_1 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_1->joinWithAND(Normal, SangatBesar);

  FuzzyRuleAntecedent *SUHUnormal_14 = new FuzzyRuleAntecedent();
  SUHUnormal_14->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_1AndSUHUnormal_14 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_1AndSUHUnormal_14->joinWithAND(PHRnormalAndGSRsangatBesar_1, SUHUnormal_14);

  FuzzyRuleConsequent *thenTingkatStressTenang_20 = new FuzzyRuleConsequent();
  thenTingkatStressTenang_20->addOutput(Tenang);

  FuzzyRule *fuzzyRule53 = new FuzzyRule(1, PHRnormalAndGSRsangatBesar_1AndSUHUnormal_14, thenTingkatStressTenang_20);
  fuzzy->addFuzzyRule(fuzzyRule53);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 54
  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_2 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_2->joinWithAND(Normal, SangatBesar);

  FuzzyRuleAntecedent *SUHUagakDingin_14 = new FuzzyRuleAntecedent();
  SUHUagakDingin_14->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_2AndSUHUagakDingin_14 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_2AndSUHUagakDingin_14->joinWithAND(PHRnormalAndGSRsangatBesar_2, SUHUagakDingin_14);

  FuzzyRuleConsequent *thenTingkatStressCemas_29 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_29->addOutput(Cemas);

  FuzzyRule *fuzzyRule54 = new FuzzyRule(1, PHRnormalAndGSRsangatBesar_2AndSUHUagakDingin_14, thenTingkatStressCemas_29);
  fuzzy->addFuzzyRule(fuzzyRule54);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 55
  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_3 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_3->joinWithAND(Normal, SangatBesar);

  FuzzyRuleAntecedent *SUHUdingin_14 = new FuzzyRuleAntecedent();
  SUHUdingin_14->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_3AndSUHUdingin_14 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_3AndSUHUdingin_14->joinWithAND(PHRnormalAndGSRsangatBesar_3, SUHUdingin_14);

  FuzzyRuleConsequent *thenTingkatStressCemas_30 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_30->addOutput(Cemas);

  FuzzyRule *fuzzyRule55 = new FuzzyRule(1, PHRnormalAndGSRsangatBesar_3AndSUHUdingin_14, thenTingkatStressCemas_30);
  fuzzy->addFuzzyRule(fuzzyRule55);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 56
  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_4 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_4->joinWithAND(Normal, SangatBesar);

  FuzzyRuleAntecedent *SUHUsangatDingin_14 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_14->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRnormalAndGSRsangatBesar_4AndSUHUsangatDingin_14 = new FuzzyRuleAntecedent();
  PHRnormalAndGSRsangatBesar_4AndSUHUsangatDingin_14->joinWithAND(PHRnormalAndGSRsangatBesar_4, SUHUsangatDingin_14);

  FuzzyRuleConsequent *thenTingkatStressCemas_31 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_31->addOutput(Cemas);

  FuzzyRule *fuzzyRule56 = new FuzzyRule(1, PHRnormalAndGSRsangatBesar_4AndSUHUsangatDingin_14, thenTingkatStressCemas_31);
  fuzzy->addFuzzyRule(fuzzyRule56);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 57
  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_1 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_1->joinWithAND(AgakCepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUnormal_15 = new FuzzyRuleAntecedent();
  SUHUnormal_15->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_1AndSUHUnormal_15 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_1AndSUHUnormal_15->joinWithAND(PHRagakCepatAndGSRsangatBesar_1, SUHUnormal_15);

  FuzzyRuleConsequent *thenTingkatStressCemas_32 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_32->addOutput(Cemas);

  FuzzyRule *fuzzyRule57 = new FuzzyRule(1, PHRagakCepatAndGSRsangatBesar_1AndSUHUnormal_15, thenTingkatStressCemas_32);
  fuzzy->addFuzzyRule(fuzzyRule57);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 58
  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_2 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_2->joinWithAND(AgakCepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUagakDingin_15 = new FuzzyRuleAntecedent();
  SUHUagakDingin_15->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_2AndSUHUagakDingin_15 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_2AndSUHUagakDingin_15->joinWithAND(PHRagakCepatAndGSRsangatBesar_2, SUHUagakDingin_15);

  FuzzyRuleConsequent *thenTingkatStressCemas_33 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_33->addOutput(Cemas);

  FuzzyRule *fuzzyRule58 = new FuzzyRule(1, PHRagakCepatAndGSRsangatBesar_2AndSUHUagakDingin_15, thenTingkatStressCemas_33);
  fuzzy->addFuzzyRule(fuzzyRule58);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 59
  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_3 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_3->joinWithAND(AgakCepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUdingin_15 = new FuzzyRuleAntecedent();
  SUHUdingin_15->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_3AndSUHUdingin_15 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_3AndSUHUdingin_15->joinWithAND(PHRagakCepatAndGSRsangatBesar_3, SUHUdingin_15);

  FuzzyRuleConsequent *thenTingkatStressCemas_34 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_34->addOutput(Cemas);

  FuzzyRule *fuzzyRule59 = new FuzzyRule(1, PHRagakCepatAndGSRsangatBesar_3AndSUHUdingin_15, thenTingkatStressCemas_34);
  fuzzy->addFuzzyRule(fuzzyRule59);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 60
  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_4 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_4->joinWithAND(AgakCepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUsangatDingin_15 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_15->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRagakCepatAndGSRsangatBesar_4AndSUHUsangatDingin_15 = new FuzzyRuleAntecedent();
  PHRagakCepatAndGSRsangatBesar_4AndSUHUsangatDingin_15->joinWithAND(PHRagakCepatAndGSRsangatBesar_4, SUHUsangatDingin_15);

  FuzzyRuleConsequent *thenTingkatStressStress_2 = new FuzzyRuleConsequent();
  thenTingkatStressStress_2->addOutput(Stress);

  FuzzyRule *fuzzyRule60 = new FuzzyRule(1, PHRagakCepatAndGSRsangatBesar_4AndSUHUsangatDingin_15, thenTingkatStressStress_2);
  fuzzy->addFuzzyRule(fuzzyRule60);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 61
  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_1 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_1->joinWithAND(Cepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUnormal_16 = new FuzzyRuleAntecedent();
  SUHUnormal_16->joinSingle(Normal1);

  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_1AndSUHUnormal_16 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_1AndSUHUnormal_16->joinWithAND(PHRcepatAndGSRsangatBesar_1, SUHUnormal_16);

  FuzzyRuleConsequent *thenTingkatStressCemas_35 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_35->addOutput(Cemas);

  FuzzyRule *fuzzyRule61 = new FuzzyRule(1, PHRcepatAndGSRsangatBesar_1AndSUHUnormal_16, thenTingkatStressCemas_35);
  fuzzy->addFuzzyRule(fuzzyRule61);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 62
  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_2 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_2->joinWithAND(Cepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUagakDingin_16 = new FuzzyRuleAntecedent();
  SUHUagakDingin_16->joinSingle(AgakDingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_2AndSUHUagakDingin_16 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_2AndSUHUagakDingin_16->joinWithAND(PHRcepatAndGSRsangatBesar_2, SUHUagakDingin_16);

  FuzzyRuleConsequent *thenTingkatStressCemas_36 = new FuzzyRuleConsequent();
  thenTingkatStressCemas_36->addOutput(Cemas);

  FuzzyRule *fuzzyRule62 = new FuzzyRule(1, PHRcepatAndGSRsangatBesar_2AndSUHUagakDingin_16, thenTingkatStressCemas_36);
  fuzzy->addFuzzyRule(fuzzyRule62);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 63
  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_3 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_3->joinWithAND(Cepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUdingin_16 = new FuzzyRuleAntecedent();
  SUHUdingin_16->joinSingle(Dingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_3AndSUHUdingin_16 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_3AndSUHUdingin_16->joinWithAND(PHRcepatAndGSRsangatBesar_3, SUHUdingin_16);

  FuzzyRuleConsequent *thenTingkatStressStress_3 = new FuzzyRuleConsequent();
  thenTingkatStressStress_3->addOutput(Stress);

  FuzzyRule *fuzzyRule63 = new FuzzyRule(1, PHRcepatAndGSRsangatBesar_3AndSUHUdingin_16, thenTingkatStressStress_3);
  fuzzy->addFuzzyRule(fuzzyRule63);
  //-------------------------------------------------------------------------------------------------------------------------//

  // Building FuzzyRule 64
  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_4 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_4->joinWithAND(Cepat, SangatBesar);

  FuzzyRuleAntecedent *SUHUsangatDingin_16 = new FuzzyRuleAntecedent();
  SUHUsangatDingin_16->joinSingle(SangatDingin);

  FuzzyRuleAntecedent *PHRcepatAndGSRsangatBesar_4AndSUHUsangatDingin_16 = new FuzzyRuleAntecedent();
  PHRcepatAndGSRsangatBesar_4AndSUHUsangatDingin_16->joinWithAND(PHRcepatAndGSRsangatBesar_4, SUHUsangatDingin_16);

  FuzzyRuleConsequent *thenTingkatStressStress_4 = new FuzzyRuleConsequent();
  thenTingkatStressStress_4->addOutput(Stress);

  FuzzyRule *fuzzyRule64 = new FuzzyRule(1, PHRcepatAndGSRsangatBesar_4AndSUHUsangatDingin_16, thenTingkatStressStress_4);
  fuzzy->addFuzzyRule(fuzzyRule64);
  //-------------------------------------------------------------------------------------------------------------------------//
}
