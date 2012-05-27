<?php
// $Id$

/**
 * 申请工作表单页面
 */
function apply_apply_job_page($job_id){
  $langcode = 'und';
	$output = "";
	/*
		$applys= entity_load('apply',array(13));
	//print debug($applys);
	$apply = $applys[13];
	//$apply->field_company_id[$langcode][]['target_id'] = 22;
	//$apply->field_company_id[$langcode][]['target_type'] = 'node';
  $apply->field_job_id[$langcode][]['target_id'] = 29;
	$apply->field_job_id[$langcode][]['target_type'] = 'node';
	//$apply = entity_save('apply',$apply);
	*/
	global $user;
	if($user->uid ==0){
	  $output = t('匿名用户无权申请实习,请您注册成为我们的会员后,再提交申请.');
		
	}else{
	  //检查是否已经申请过了。
    $flag = apply_is_applyed($job_id);
//$flag = FALSE;
		if($flag){
      $output = t('您已经申请了该职位,您现在可以申请其它职位.');
		}else{
     $form = drupal_get_form('apply_apply_job_form',$job_id);
	 $output .= drupal_render($form);
		}
	}
	return $output;
}

function apply_apply_job_form($form, &$form_state, $job_id){
  $form = array();
	global $user;
	$company_id = 0;
	$company_id = db_select('og_membership','m')
	->fields('m',array('gid'))
	->condition('entity_type','node')
	->condition('etid',$job_id)
	->condition('group_type','node')
	//->condition('field_name','og_group_ref')
	->range(0,1)
	->execute()
	->fetchField();
	
	$resume_options = array(
	  '' => t('请选择您的简历'),
	);
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node');
	$query->entityCondition('bundle', 'resume');
	
	$query->propertyCondition('uid', $user->uid);
	$query->propertyOrderBy('created', 'ASC');
	//$query->range(0,1);
	$result = $query->execute();
	
	$nids = array();
	if(!empty($result) && isset($result['node'])){
		$nids = array_keys($result['node']);
		$resumes = node_load_multiple($nids);
		foreach($resumes as $resume){
		  $resume_options[$resume->nid] = $resume->title;
		}
	}else{
	  drupal_set_message('您还没有添加简历，现在就去创建');
	}
	$form['company_id'] = array(
		'#type' => 'value',
		'#value' => $company_id,
  );
	$form['job_id'] = array(
		'#type' => 'value',
		'#value' => $job_id,
  );
	$form['uid'] = array(
		'#type' => 'value',
		'#value' => $user->uid,
  );	
  $form['resume_id'] = array(
		'#type' => 'select',
		'#title' => t('简历'),
		'#required' => TRUE,
		'#options' => $resume_options,
		//'#attributes' => array('class' => array('company_name')),
  );
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('提交'),
		//'#required' => TRUE,
		//'#attributes' => array('class' => array('company_name')),
  );
	return $form;
}

function apply_apply_job_form_submit($form, &$form_state){
  //global $language;
  //$langcode = $language->language;
	$langcode = 'und';
	
  $job_id = $form_state['values']['job_id'];
  $uid = $form_state['values']['uid'];
	$resume_id = $form_state['values']['resume_id'];
	$company_id = $form_state['values']['company_id'];
	$created = time();
	$apply = new stdClass();
	$apply->uid = $uid;
	$apply->created = $created;
	$apply->entity_type = 'apply';
	$apply->type = 'apply';
	$apply->bundle = 'apply';
	$apply->field_resume_id[$langcode][]['target_id'] = $resume_id;
	$apply->field_resume_id[$langcode][]['target_type'] = 'node';
	$apply->field_job_id[$langcode][]['target_id'] = $job_id;
	$apply->field_job_id[$langcode][]['target_type'] = 'node';
	$apply->field_company_id[$langcode][]['target_id'] = $company_id;
	$apply->field_company_id[$langcode][]['target_type'] = 'node';
	//$entity = $apply;
	//$applys= entity_load('apply',array(9));
	//print debug($job_id);
	//print debug($resume_id);
	//print debug($langcode);
	/*
	$info = entity_get_info('apply');
	  if (!empty($info['entity keys']['bundle'])) {
    // Explicitly fail for malformed entities missing the bundle property.
    if (!isset($entity->{$info['entity keys']['bundle']}) || $entity->{$info['entity keys']['bundle']} === '') {
      throw new EntityMalformedException(t('Missing bundle property on entity of type entity_type.'));
    }
    $bundle = $entity->{$info['entity keys']['bundle']};
  }*/
	//print debug($info);
	entity_save('apply',$apply);
	//entity_save('apply',$apply);
	//return $form;
}
/*
function apply_user_job_apply_record($user){
	$output = "";
	$output .= t('To Do');
	return $output;
}


function apply_company_job_apply_record($company_id){
	$output = "";
  $output .= t('To Do');
	return $output;
}
*/